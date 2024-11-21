#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

#define PACKET_MAX_SIZE 1000

#define handle_error(error) \
  do { \
    fprintf(stderr,"%s : %s",error,strerror(errno)); \
    exit(EXIT_FAILURE); \
  } while(true) 

typedef enum {
  PACKET_TYPE_PLAYER_STATE,
  PACKET_TYPE_PLAYER_ATTRIBUTES,
  PACKET_TYPE_ICMP,
  PACKET_TYPE_NONE
} packet_type_e;

typedef enum {
    FIELD_TYPE_NONE,
    FIELD_TYPE_INT,
    FIELD_TYPE_FLOAT,
    FIELD_TYPE_STR,
    FIELD_TYPE_TIME,
    FIELD_TYPE_BOOL
} field_type_e;

typedef struct {

  uint16_t type;
  uint16_t size;
  struct sockaddr_in addr_in;

  union {
    struct {
      time_t time;
    } icmp;
    struct {
      float x;
      float y;
      float z;

      float dx;
      float dy;
      float dz;
      int16_t orientation;
      bool jump;
      bool shift;
    } player_state;
    struct {
      bool sleep;
      bool paralyzed;
      bool dying;

    } player_attributes;
  } payload;
} packet_t;

typedef struct {
    const char *name;
    int size;
    int offset;
    field_type_e type;
} packet_field_t;

typedef struct {
    uint8_t type;
    packet_field_t fields[10];
} packet_desc_t;

const packet_desc_t PACKET_DESCS[PACKET_TYPE_NONE] = {
  [PACKET_TYPE_PLAYER_STATE] = { 
    .type = PACKET_TYPE_PLAYER_STATE, 
    .fields = {
      { .name = "x", .size = sizeof(((packet_t *)NULL)->payload.player_state.x), .offset = offsetof(packet_t,payload.player_state.x), .type = _Generic((((packet_t *)NULL)->payload.player_state.x), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "y", .size = sizeof(((packet_t *)NULL)->payload.player_state.y), .offset = offsetof(packet_t,payload.player_state.y), .type = _Generic((((packet_t *)NULL)->payload.player_state.y), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "z", .size = sizeof(((packet_t *)NULL)->payload.player_state.z), .offset = offsetof(packet_t,payload.player_state.z), .type = _Generic((((packet_t *)NULL)->payload.player_state.z), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "dx", .size = sizeof(((packet_t *)NULL)->payload.player_state.dx), .offset = offsetof(packet_t,payload.player_state.dx), .type = _Generic((((packet_t *)NULL)->payload.player_state.dx), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "dy", .size = sizeof(((packet_t *)NULL)->payload.player_state.dy), .offset = offsetof(packet_t,payload.player_state.dy), .type = _Generic((((packet_t *)NULL)->payload.player_state.dy), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "dz", .size = sizeof(((packet_t *)NULL)->payload.player_state.dz), .offset = offsetof(packet_t,payload.player_state.dz), .type = _Generic((((packet_t *)NULL)->payload.player_state.dz), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "orientation", .size = sizeof(((packet_t *)NULL)->payload.player_state.orientation), .offset = offsetof(packet_t,payload.player_state.orientation), .type = _Generic((((packet_t *)NULL)->payload.player_state.orientation), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "jump", .size = sizeof(((packet_t *)NULL)->payload.player_state.jump), .offset = offsetof(packet_t,payload.player_state.jump), .type = _Generic((((packet_t *)NULL)->payload.player_state.jump), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "shift", .size = sizeof(((packet_t *)NULL)->payload.player_state.shift), .offset = offsetof(packet_t,payload.player_state.shift), .type = _Generic((((packet_t *)NULL)->payload.player_state.shift), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "Sentinel", .size = 0, .offset = 0, .type = FIELD_TYPE_NONE},
    },
  },
  [PACKET_TYPE_PLAYER_ATTRIBUTES] = { 
    .type = PACKET_TYPE_PLAYER_ATTRIBUTES, 
    .fields = {
      { .name = "sleep", .size = sizeof(((packet_t *)NULL)->payload.player_attributes.sleep), .offset = offsetof(packet_t,payload.player_attributes.sleep), .type = _Generic((((packet_t *)NULL)->payload.player_attributes.sleep), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "paralyzed", .size = sizeof(((packet_t *)NULL)->payload.player_attributes.paralyzed), .offset = offsetof(packet_t,payload.player_attributes.paralyzed), .type = _Generic((((packet_t *)NULL)->payload.player_attributes.paralyzed), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "dying", .size = sizeof(((packet_t *)NULL)->payload.player_attributes.dying), .offset = offsetof(packet_t,payload.player_attributes.dying), .type = _Generic((((packet_t *)NULL)->payload.player_attributes.dying), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "Sentinel", .size = 0, .offset = 0, .type = FIELD_TYPE_NONE},
    },
  },
  [PACKET_TYPE_ICMP] = { 
    .type = PACKET_TYPE_ICMP, 
    .fields = {
      { .name = "time", .size = sizeof(((packet_t *)NULL)->payload.icmp.time), .offset = offsetof(packet_t,payload.icmp.time), .type = _Generic((((packet_t *)NULL)->payload.icmp.time), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "Sentinel", .size = 0, .offset = 0, .type = FIELD_TYPE_NONE},
    },
  },
};

typedef uint8_t status_code_t;

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
  bytes_sent = sendto(sockfd,
                buffer,
                sizeof(buffer),
                0,
                (struct sockaddr*)&packet->addr_in,
                sizeof(packet->addr_in));
  if(0 > bytes_sent) {
    fprintf(stderr,"SendTO FAILED : %s",strerror(errno));
    return 404;
  }
  // byte_ptr = (uint8_t *)buffer; 

  // packet_t receive_packet_v2;
  // packet_t *receive_packet = &receive_packet_v2;
  // memcpy(&receive_packet->type, byte_ptr, sizeof(receive_packet->type));
  // byte_ptr += sizeof(receive_packet->type);
  // memcpy(&receive_packet->size, byte_ptr, sizeof(receive_packet->size));
  // byte_ptr += sizeof(receive_packet->size);
  // memcpy(&receive_packet->payload.icmp.time, byte_ptr, sizeof(receive_packet->payload.icmp.time));
  // printf("%d, %d, %s",receive_packet->type,receive_packet->size,ctime(&receive_packet->payload.icmp.time));

  return 200;
}

status_code_t receive_packet(int sockfd,packet_t *packet) {
  float buffer[PACKET_MAX_SIZE];
  uint8_t *byte_ptr = (uint8_t *)buffer;
  socklen_t size;
  int bytes_read;
  bytes_read = recvfrom(sockfd,
                  buffer,
                  sizeof(buffer),
                  0,
                  (struct sockaddr *)&packet->addr_in,
                  &size); 
  if(0 > bytes_read){
    fprintf(stderr,"RecvFROM Failed : %s",strerror(errno));
    return 404;
  }
  printf("Bytes read from network : %d",bytes_read);
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

int server_socket_init() {
  struct sockaddr_in addr_in = {
    .sin_family = AF_INET,
    .sin_port = 36895,
    .sin_addr = {
      .s_addr = INADDR_ANY,
    },
  };

  int sockfd = socket(AF_INET,SOCK_DGRAM,0);
  if(0 > sockfd)
    handle_error("Socket");
  if(0 > bind(sockfd,
              (struct sockaddr *)&addr_in,
              sizeof(addr_in)))
    handle_error("Bind");
  return sockfd;
}

int client_socket_init() {
  struct sockaddr_in addr_in = {
    .sin_family = AF_INET,
    .sin_port = 36895,
    .sin_addr = {
      .s_addr = 16777343,
    },
  };

  int sockfd = socket(AF_INET,SOCK_DGRAM,0);
  if(0 > sockfd)
    handle_error("Socket");

  if(0 > connect(sockfd,(struct sockaddr *)&addr_in,sizeof(addr_in)))
    handle_error("Bind");

  return sockfd;
}

int main(int argc,char *argv[]) {
  int sockfd = client_socket_init();
  int i = 0;

  while(true) {
    packet_t packet;
    packet.type = PACKET_TYPE_ICMP;
    packet.addr_in.sin_family = AF_INET;
    packet.addr_in.sin_port = 36895;
    packet.addr_in.sin_addr.s_addr = 16777343;
    packet.payload.icmp.time = time(NULL);
    packet.size = 256;
    // printf("%s",ctime(&packet.payload.icmp.time));
    status_code_t status = send_packet(sockfd,&packet);
    usleep(100000);
  }
}
