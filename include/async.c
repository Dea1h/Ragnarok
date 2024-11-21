#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

#define handle_error(error,err)                      /
        do {                                         /
          fprintf(stderr,error,strerror(err));       /
          return NULL;                               /
        } while(true)                                

unsigned long int async(void*(*start_routine)(void *),void *restrict start_arg,
            void*(callback_routine)(void *),void *restrict callback_arg){
  pthread_t thread
  if(0 > pthread_create(&thread,NULL,start_routine,start_arg))
    handle_error("phread_create : %s");
  return thread;
}

void **await(pthread_t thread,void **retval){
  pthread_join(thread,retval);
  return retval;
}
