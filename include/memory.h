#ifndef MEMORY_H
#define MEMORY_H

void *mpool(void *addr,size_t size,int prot,
            int flags,int fildes,off_t off);

void mrel(void *addr,size_t size);

typedef struct {
  page page[];
} page_table;

typedef struct {
  void * mem;
  size_t size;
} page;
#endif
