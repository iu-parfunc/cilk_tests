#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/eventfd.h>
#include <stdint.h>

// prototypes
void acceptLoop();
void startWorkerThread(int);
void *workerLoop(void *);
void receiveLoop(int, char []);

// constants
#define MAX_NUM_WORKERS 120
#define BACKLOG 600
#define MAX_EVENTS 500
#define NUM_CLIENTS 1000
#define SHOW_REQUEST 1
#define READ_EVENT_FD
#define SHOW_PEAK_PERFORMANCE 0
#ifdef SHOW_PEAK_PERFORMANCE
#undef READ_EVENT_FD
#undef SHOW_REQUEST
#endif

char* EXPECTED_HTTP_REQUEST;
int EXPECTED_RECV_LEN;
int PORT_NUM;
size_t RESPONSE_LEN;

volatile int num_clients;
volatile int num_requests;
__thread unsigned int nreq = 0;
double start_time;
double end_time;

char RESPONSE[] =
"HTTP/1.1 200 OK\r\n"
"Date: Tue, 09 Oct 2012 16:36:18 GMT\r\n"
"Content-Length: 151\r\n"
"Server: Mighttpd/2.8.1\r\n"
"Last-Modified: Mon, 09 Jul 2012 03:42:33 GMT\r\n"
"Content-Type: text/html\r\n\r\n"
"<html>\n<head>\n<title>Welcome to nginx!</title>\n</head>\n"
"<body bgcolor=\"white\" text=\"black\">\n"
"<center><h1>Welcome to nginx!</h1></center>\n</body>\n</html>\n";

#if !(defined SHOW_PEAK_PERFORMANCE)
int evfd = -1;
#endif

static inline
double getticks(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (double) (tv.tv_sec * 1e6 + tv.tv_usec);
}

static inline
double elapsed(double t1, double t0) {
  return (double) (t1 - t0);
}

static void
server_shutdown(void) {
    end_time = elapsed(getticks(), start_time);
    printf("Number of requests: %u.\n", num_requests);
    // Throughput
    printf("SELFTIMED: %lf\n", num_requests*1e6/end_time);
    exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf( "usage: %s #workers <port number>\n", argv[0] );
    return -1;
  }

  /*asprintf(&EXPECTED_HTTP_REQUEST, "GET / HTTP/1.1\r\nHost: 129.79.247.33:%d\r\nUser-Agent: weighttp/0.3\r\nConnection: keep-alive\r\n\r\n", atoi(argv[2]));*/
  asprintf(&EXPECTED_HTTP_REQUEST, "GET / HTTP/1.1\r\nHost: 127.0.0.1:%d\r\nUser-Agent: weighttp/0.3\r\nConnection: keep-alive\r\n\r\n", atoi(argv[2]));
  PORT_NUM=atoi(argv[2]);

  EXPECTED_RECV_LEN = strlen(EXPECTED_HTTP_REQUEST);
  RESPONSE_LEN = strlen(RESPONSE);

  printf("Length of request: %d;  response: %d\n", EXPECTED_RECV_LEN, RESPONSE_LEN);

  int numWorkers = atoi(argv[1]);
  if (numWorkers >= MAX_NUM_WORKERS) {
    printf("error: number of workers must be less than %d\n", MAX_NUM_WORKERS);
    return -1;
  }

  num_clients = -1;
  num_requests = 0;
  //atexit(server_shutdown);

  acceptLoop();
  return 0;
}

void startWorkerThread(int w) {
  pthread_t thread;
  if (pthread_create(&thread, NULL, workerLoop, (void *)(unsigned long) w)) {
    perror("pthread_create");
    exit(-1);
  }
  return;
}

void *workerLoop(void * arg) {
  int epfd = (int)(unsigned long) arg;
  int n;
  ssize_t m;
  int i;
  int sock;
  char recvbuf[1000];

  receiveLoop(epfd, recvbuf);
  pthread_exit(NULL);
}

void receiveLoop(int sock, char recvbuf[]) {
  ssize_t m;
  int numSent;
  int remaining = EXPECTED_RECV_LEN;
  int nc;

  while(1) {
    m = recv(sock, recvbuf, remaining, 0);
    if (m > 0) {
      remaining = remaining - m;
      if (remaining == 0) {
        remaining = EXPECTED_RECV_LEN;
        numSent = send(sock, RESPONSE, RESPONSE_LEN, 0);
        /*printf(".");*/
        if (numSent == -1) {
          perror("send failed");
          exit(-1);
        }
        if (numSent != RESPONSE_LEN) {
          perror("partial send");
          exit(-1);
        }
      }
    } else if (m == 0) {
      nc = __sync_sub_and_fetch(&num_clients, 1);
      __sync_fetch_and_add(&num_requests, nreq);
      if (nc == 0)
        server_shutdown();
    }
    nreq++;
  }
}

void acceptLoop()
{
  int sd;
  struct sockaddr_in addr;
  socklen_t alen = sizeof(addr);
  short port = PORT_NUM;
  int sock_tmp;
  int current_worker = 0;
  int current_client = 0;
  int optval;

  if (-1 == (sd = socket(PF_INET, SOCK_STREAM, 0))) {
    printf("socket: error: %d\n",errno);
    exit(-1);
  }

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  optval = 1;
  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
  if (bind(sd, (struct sockaddr*)&addr, sizeof(addr))) {
    printf("bind error: %d\n",errno);
    exit(-1);
  }
  if (listen(sd, BACKLOG)) {
    printf("listen error: %d\n",errno);
    exit(-1);
  }
  while(1) {
    if (-1 == (sock_tmp = accept(sd, (struct sockaddr*)&addr, &alen))) {
      printf("Error %d doing accept", errno);
      exit(-1);
    }
    if (num_clients == -1) {
      __sync_fetch_and_add(&num_clients, 1);
      start_time = getticks();
    }
    __sync_fetch_and_add(&num_clients, 1);
    startWorkerThread(sock_tmp);
  }
}
