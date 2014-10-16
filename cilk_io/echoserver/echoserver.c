
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
/* For inet_ntoa. */
#include <arpa/inet.h>

#include <cilk/cilk.h>
#include <cilk/concurrent_cilk.h>

#define SERVER_PORT 5555

#define BUF_MAX 256


void do_echo(int fd) {
  char recvbuf[BUF_MAX];
  int rlen = BUF_MAX;
  int wlen = BUF_MAX;
  while (rlen > 0 && wlen > 0) {
    rlen = cilk_read(fd, recvbuf, BUF_MAX);
    wlen = cilk_write(fd, recvbuf, rlen);
  }
  close(fd);
}

void echo_server(int listen_fd) {
  char welcome[] = "Hello client!";
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);

  while (1) {
    printf("Calling cilk_accept..\n");
    int fd = cilk_accept(listen_fd, (struct sockaddr*)&addr, &addr_len);
    assert(fd >= 0);
    cilk_write(fd, welcome, strlen(welcome));
    cilk_spawn do_echo(fd);
  }
}

int main(int argc, char** argv) {

  int listen_fd;
  struct sockaddr_in listen_addr;
  int reuseaddr_on = 1;

  listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd < 0)
    err(1, "listen failed");
  if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on,
        sizeof(reuseaddr_on)) == -1)
    err(1, "setsockopt failed");

  memset(&listen_addr, 0, sizeof(listen_addr));
  listen_addr.sin_family = AF_INET;
  listen_addr.sin_addr.s_addr = INADDR_ANY;
  listen_addr.sin_port = htons(SERVER_PORT);

  if (bind(listen_fd, (struct sockaddr *)&listen_addr, sizeof(listen_addr)) < 0) {
    err(1, "bind failed");
  }

  if (listen(listen_fd, 4) < 0) {
    err(1, "listen failed");
  }

  if (cilk_io_init()) {
    err(1, "cilk_io_init() failed");
  }

  cilk_spawn echo_server(listen_fd);
  cilk_sync;

  cilk_io_teardown();
  printf("Exiting server..\n");

}
