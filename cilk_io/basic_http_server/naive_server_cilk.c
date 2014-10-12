#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/eventfd.h>
#include <stdint.h>
#include <cilk/cilk.h>

// prototypes
void acceptLoop();
void *workerLoop(void *);
void receiveLoop(int, char []);
void setNonBlocking(int);

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

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf( "usage: %s #workers <port number>\n", argv[0] );
    return -1;
  }

  asprintf(&EXPECTED_HTTP_REQUEST, "GET / HTTP/1.1\r\nHost: 129.79.247.33:%d\r\nUser-Agent: weighttp/0.3\r\nConnection: keep-alive\r\n\r\n", atoi(argv[2]));
  PORT_NUM=atoi(argv[2]);

  EXPECTED_RECV_LEN = strlen(EXPECTED_HTTP_REQUEST);
  RESPONSE_LEN = strlen(RESPONSE);

  printf("Length of request: %d;  response: %d\n", EXPECTED_RECV_LEN, RESPONSE_LEN);

  int numWorkers = atoi(argv[1]);
  if (numWorkers >= MAX_NUM_WORKERS) {
    printf("error: number of workers must be less than %d\n", MAX_NUM_WORKERS);
    return -1;
  }

  acceptLoop();
  return 0;
}

void *workerLoop(void * arg) {
  int epfd = (int)(unsigned long) arg;
  int n;
  ssize_t m;
  int i;
  int sock;
  char recvbuf[1000];

  receiveLoop(epfd, recvbuf);
}

void receiveLoop(int sock, char recvbuf[]) {
  ssize_t m;
  int numSent;
  int remaining = EXPECTED_RECV_LEN;

  while(1) {
    m = recv(sock, recvbuf, remaining, 0);
    if (m==0) break;
    if (m > 0) {
      remaining = remaining - m;
      if (remaining == 0) {
        remaining = EXPECTED_RECV_LEN;
        numSent = send(sock, RESPONSE, RESPONSE_LEN, 0);
        /*printf("%s\n", RESPONSE);*/
        if (numSent == -1) {
          perror("send failed");
          exit(-1);
        }
        if (numSent != RESPONSE_LEN) {
          perror("partial send");
          exit(-1);
        }
      }
    }
    if (m==-1) {
      if (errno==EAGAIN) {
        continue;
      } else {
        perror("recv");
        exit(-1);
      }
    }
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
    setNonBlocking(sock_tmp);
    cilk_spawn workerLoop((void*)(unsigned long)sock_tmp);
  }
}

void setNonBlocking(int fd) {
  int flags;
  if (-1 == (flags = fcntl(fd, F_GETFL, 0))) {
    perror("Getting NONBLOCKING failed.\n");
    exit(-1);
  }
  if ( fcntl(fd, F_SETFL, flags | O_NONBLOCK ) < 0 ) {
    perror("Setting NONBLOCKING failed.\n");
    exit(-1);
  }
  return;
}