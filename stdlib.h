#ifndef MALLOC_H
#define MALLOC_H
#define NULL                0
typedef unsigned int        size_t;

void *      malloc(size_t size);
void        free(void *ptr);
#endif
