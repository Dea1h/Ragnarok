#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include <netinet/in.h>

#define PACKET_MAX_SIZE 4096

#define PACKET_TYPES_ITER(_F, ...) \
    _F(PLAYER_STATE, player_state, 0, __VA_ARGS__) \
    _F(PLAYER_ATTRIBUTES, player_attributes, 1, __VA_ARGS__) \
    _F(ICMP, icmp, 2, __VA_ARGS__)

#define PACKET_TYPES_ITER_STRUCT(UNAME, LNAME, ID, ...) \
[PACKET_TYPE_##UNAME] = { \
    .type = PACKET_TYPE_##UNAME, \
    .fields = { \
        PACKET_##UNAME##_FIELDS(PACKET_TYPES_ITER_FIELDS, LNAME, __VA_ARGS__) \
    }, \
},

#define PACKET_TYPES_ITER_FIELDS(FIELD_NAME, LNAME, ...) { \
    .name = #FIELD_NAME, \
    .size = sizeof_field(FIELD_NAME, LNAME), \
    .offset = offsetof(packet_t,payload.LNAME.FIELD_NAME), \
    .type = FIELD_TYPE_OF(((packet_t *)NULL)->payload.LNAME.FIELD_NAME), \
},

#define FIELD_TYPE_OF(_T) _Generic((_T), \
    int: FIELD_TYPE_INT, \
    float: FIELD_TYPE_FLOAT, \
    bool: FIELD_TYPE_BOOL, \
    time_t: FIELD_TYPE_TIME, \
    default: FIELD_TYPE_NONE \
)

#define PACKET_PLAYER_STATE_FIELDS(_F, LNAME, ...) \
    _F(x, LNAME,  __VA_ARGS__) \
    _F(y, LNAME, __VA_ARGS__) \
    _F(z, LNAME, __VA_ARGS__) \
    _F(dx, LNAME, __VA_ARGS__) \
    _F(dy, LNAME, __VA_ARGS__) \
    _F(dz, LNAME, __VA_ARGS__) \
    _F(heading, LNAME, __VA_ARGS__) \
    _F(jump, LNAME, __VA_ARGS__) \
    _F(shift, LNAME, __VA_ARGS__)

#define PACKET_PLAYER_ATTRIBUTES_FIELDS(_F, LNAME, ...) \
    _F(paralyzed, LNAME, __VA_ARGS__) \
    _F(hungry, LNAME, __VA_ARGS__)

#define PACKET_ICMP_FIELDS(_F, LNAME, ...) \
  _F(time, LNAME, __VA_ARGS__)

#define sizeof_field(_f, _l) sizeof(((packet_t *)NULL)->payload._l._f)

typedef enum {
  PACKET_TYPE_PLAYER_STATE,
  PACKET_TYPE_PLAYER_ATTRIBUTES,
  PACKET_TYPE_ICMP,
  PACKET_TYPE_SENTINEL
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

      int16_t heading;

      bool jump;
      bool shift;
    } player_state;
    struct {
      bool paralyzed;
      bool hungry;
    } player_attributes;
  } payload;
} packet_t;

typedef struct {
    const char *name;
    size_t size;
    size_t offset;
    field_type_e type;
} packet_field_t;

typedef struct {
    uint8_t type;
    packet_field_t fields[10];
} packet_desc_t;

typedef uint8_t status_code_t;

status_code_t send_packet(int sockfd,packet_t *packet);

status_code_t receive_packet(int sockfd,packet_t *packet);

extern const packet_desc_t PACKET_DESCS[];
#endif
