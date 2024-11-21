typedef enum {
  SOME,
  NONE,
};

typedef enum {
  OK,
  ERR,
};

#define __option(T)     \
  typedef struct {      \
    T data;             \
    option_t_e option;  \
  } option_##T; 

#define __result(T)     \
  typedef struct {      \
    T data;             \
    result_t_e result;  \
  };

/*RESULT*/

__result(int8_t);
__result(int16_t);
__result(int32_t);
__result(int64_t);
__result(uint8_t);
__result(uint16_t);
__result(uint32_t);
__result(uint64_t);
__result(char);
__result(float);
__result(double);
__result(bool);


__result(int8_t);
__result(int16_t);
__result(int32_t);
__result(int64_t);
__result(uint8_t);
__result(uint16_t);
__result(uint32_t);
__result(uint64_t);
__result(char);
__result(float);
__result(double);
__result(bool);
