#include <stdio.h>
#include <time.h>
#include "packet.h"
#include "network.h"
#include "error.h"
#include <sys/socket.h>

int main(int argc,char *argv[]) {
  struct sockaddr_in addr_in = {
    .sin_family = AF_INET,
    .sin_port = 36895,
    .sin_addr = {
      .s_addr = INADDR_ANY,
    },
  };
  int sockfd = server_socket_init(AF_INET,SOCK_DGRAM,0,&addr_in);

  while(true) {
    packet_t packet;
    receive_packet(sockfd,&packet);
    printf("Ping client : %s",ctime(&packet.payload.icmp.time));
  }
}
