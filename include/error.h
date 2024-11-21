#ifndef ERROR_H
#define ERROR_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define handle_error(error) \
  do { \
    fprintf(stderr,"%s : %s",error,strerror(errno)); \
    exit(EXIT_FAILURE); \
  } while(true) 

#endif
