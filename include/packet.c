#include <stdint.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "network.h"
#include "error.h"
#include "packet.h"

typedef uint8_t status_code_t;

status_code_t receive_packet(int sockfd,packet_t *packet) {
  float buffer[PACKET_MAX_SIZE];
  uint8_t *byte_ptr = (uint8_t *)buffer;
  socklen_t size = sizeof(packet->addr_in);
  int bytes_read;
  bytes_read = recvfrom(sockfd,
                  buffer,
                  sizeof(buffer),
                  0,
                  (struct sockaddr *)&packet->addr_in,
                  &size);
  if(0 > bytes_read) {
    fprintf(stderr,"RecvFROM Failed : %s",strerror(errno));
    return 404;
  }
  printf("Sizeof buffer : %d\n",sizeof(buffer));
  printf("Bytes received : %d\n",bytes_read);
  memcpy(packet, byte_ptr, sizeof(packet->type) + sizeof(packet->size));
  byte_ptr += sizeof(packet->type) + sizeof(packet->size);
  const packet_desc_t *desc = &PACKET_DESCS[packet->type];
  for(int i = 0;
      desc->fields[i].type != FIELD_TYPE_NONE;
      i++) {
    const packet_field_t *field = &desc->fields[i];
    memcpy((char *)packet + field->offset, byte_ptr, field->size);
    byte_ptr += field->size;
  }
  return 200;
}

status_code_t send_packet(int sockfd,packet_t *packet) {
  float buffer[PACKET_MAX_SIZE];
  uint8_t *byte_ptr = (uint8_t *)buffer;
  memcpy(byte_ptr, packet, sizeof(packet->type) + sizeof(packet->size));
  byte_ptr += sizeof(packet->type) + sizeof(packet->size);
  const packet_desc_t *desc = &PACKET_DESCS[packet->type];
  for(int i = 0;
      desc->fields[i].type != FIELD_TYPE_NONE;
      i++) {
    const packet_field_t *field = &desc->fields[i];
    memcpy(byte_ptr, (uint8_t *)packet + field->offset, field->size);
    byte_ptr += field->size;
  }
  int bytes_sent;
  if(0 > sendto(sockfd,
                buffer,
                sizeof(buffer),
                0,
                (struct sockaddr*)&packet->addr_in,
                sizeof(packet->addr_in))) {
    fprintf(stderr,"SendTO FAILED : %s",strerror(errno));
    return 404;
  }
  return 200;
}

const packet_desc_t PACKET_DESCS[] = {
  PACKET_TYPES_ITER(PACKET_TYPES_ITER_STRUCT)
};
