#ifndef QUEUE_H
#define QUEUE_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define TYPE void*

typedef struct q_t queue_t;

//pop: deletes the first element 
void pop(queue_t*);
//push: adds an element(e) at the end
void push(queue_t*, TYPE e);
//get: get the first element
TYPE get(queue_t*);
//size: get the current number of elements
long size(queue_t*);
//get the current max size of memory space that allocated
long mem_size(queue_t*);
//print queue to the std out: (1, ..., 20)
void out_q(queue_t*);

//Factory-functions:
//threadsafe: create(mutex*)
queue_t* create_thr(pthread_mutex_t*, long);
//initalise with specific size(it is the raise size too): create(int)
//Both: create(int, mutex*)
#endif
