#include <sys/socket.h>
#include <netinet/in.h>

#include "network.h"
#include "error.h"


int server_socket_init(int domain,int type,int protocol,struct sockaddr_in *addr_in) {
  int sockfd = socket(domain,type,protocol);
  if(0 > sockfd)
    handle_error("Socket");
  if(0 > bind(sockfd,
              (struct sockaddr *)addr_in,
              sizeof(*addr_in)))
    handle_error("Bind");
  return sockfd;
}

int client_socket_init(int domain,int type,int protocol,struct sockaddr_in *addr_in) {
  int sockfd = socket(domain,type,protocol);
  if(0 > sockfd)
    handle_error("Socket");

  if(0 > connect(sockfd,
                (struct sockaddr *)addr_in,
                sizeof(addr_in)))
    handle_error("Bind");

  return sockfd;
}
