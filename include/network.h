#ifndef NETWORK_H
#define NETWORK_H
#include <netinet/in.h>

typedef struct { 
  /*port the server bind on */
  in_port_t port;
  int sockfd;

} 

int server_socket_init(int domain,int type,int protocol,struct sockaddr_in *addr_in);
int client_socket_init(int domain,int type,int protocol,struct sockaddr_in *addr_in);

#endif
