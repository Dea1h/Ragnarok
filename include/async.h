#ifndef ASYNC_H
#define ASYNC_H
void *async(void*(*start_routine)(void *),void *restrict start_arg,void*(*callback_routine)(void *),void *restrict callback_arg);
#endif
