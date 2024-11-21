typedef enum {
  PACKET_TYPE_PLAYER_STATE,
  PACKET_TYPE_PLAYER_ATTRIBUES,
  PACKET_TYPE_ICMP,
  PACKET_TYPE_NONE
} packet_type_e;

typedef enum {
    FIELD_TYPE_NONE,
    FIELD_TYPE_INT,
    FIELD_TYPE_FLOAT,
    FIELD_TYPE_STR,
    FIELD_TYPE_BOOL,
    // Add more field types as needed
} field_type_e;

typedef uint8_t status_code_t;

typedef struct {
  /* TYPE WILL BE THE STRUCTURE THAT IS FILLED IN THE UNION */
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
      bool paralized;
      bool dying;
      /* TODO ADD MORE ATTRIBUTES TO PLAYER_ATTRIBUTES*/
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
      { .name = "x", .size = sizeof(((packet_t *)NULL)->payload.player_state.x), .offset = offsetof(packet_t,payload.player_state.x), .type = _Generic((((packet_t *NULL)->payload.player_state.x)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "y", .size = sizeof(((packet_t *)NULL)->payload.player_state.y), .offset = offsetof(packet_t,payload.player_state.y), .type = _Generic((((packet_t *NULL)->payload.player_state.y)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "z", .size = sizeof(((packet_t *)NULL)->payload.player_state.z), .offset = offsetof(packet_t,payload.player_state.z), .type = _Generic((((packet_t *NULL)->payload.player_state.z)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "dx", .size = sizeof(((packet_t *)NULL)->payload.player_state.dx), .offset = offsetof(packet_t,payload.player_state.dx), .type = _Generic((((packet_t *NULL)->payload.player_state.dx)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "dy", .size = sizeof(((packet_t *)NULL)->payload.player_state.dy), .offset = offsetof(packet_t,payload.player_state.dy), .type = _Generic((((packet_t *NULL)->payload.player_state.dy)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "dz", .size = sizeof(((packet_t *)NULL)->payload.player_state.dz), .offset = offsetof(packet_t,payload.player_state.dz), .type = _Generic((((packet_t *NULL)->payload.player_state.dz)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "orientation", .size = sizeof(((packet_t *)NULL)->payload.player_state.orientation), .offset = offsetof(packet_t,payload.player_state.orientation), .type = _Generic((((packet_t *NULL)->payload.player_state.orientation)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "jump", .size = sizeof(((packet_t *)NULL)->payload.player_state.jump), .offset = offsetof(packet_t,payload.player_state.jump), .type = _Generic((((packet_t *NULL)->payload.player_state.jump)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "shift", .size = sizeof(((packet_t *)NULL)->payload.player_state.shift), .offset = offsetof(packet_t,payload.player_state.shift), .type = _Generic((((packet_t *NULL)->payload.player_state.shift)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
    },
  },
  [PACKET_TYPE_PLAYER_ATTRIBUTES] = { 
    .type = PACKET_TYPE_PLAYER_ATTRIBUTES, 
    .fields = {
      { .name = "sleep", .size = sizeof(((packet_t *)NULL)->payload.player_attributes.sleep), .offset = offsetof(packet_t,payload.player_attributes.sleep), .type = _Generic((((packet_t *NULL)->payload.player_attributes.sleep)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "paralyzed", .size = sizeof(((packet_t *)NULL)->payload.player_attributes.paralyzed), .offset = offsetof(packet_t,payload.player_attributes.paralyzed), .type = _Generic((((packet_t *NULL)->payload.player_attributes.paralyzed)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
      { .name = "dying", .size = sizeof(((packet_t *)NULL)->payload.player_attributes.dying), .offset = offsetof(packet_t,payload.player_attributes.dying), .type = _Generic((((packet_t *NULL)->payload.player_attributes.dying)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
    },
  },
  [PACKET_TYPE_ICMP] = { 
    .type = PACKET_TYPE_ICMP, 
    .fields = { { .name = "time", .size = sizeof(((packet_t *)NULL)->payload.LNAME.time), .offset = offsetof(packet_t,payload.LNAME.time), .type = _Generic((((packet_t *NULL)->payload.LNAME.time)), int: FIELD_TYPE_INT, float: FIELD_TYPE_FLOAT, bool: FIELD_TYPE_BOOL, time_t: FIELD_TYPE_TIME, default: FIELD_TYPE_NONE ), },
    },
  },
}
