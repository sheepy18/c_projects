#ifndef QUEUE_H
#define QUEUE_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//Error code 
#include "ecodes.h"

#define TYPE void*



typedef struct q_t queue_t;

//pop: deletes the first element 
int pop(queue_t*);
//push: adds an element(e) at the end
int push(queue_t*, TYPE e);
//get: get the first element
TYPE get(queue_t*);
//size: get the current number of elements
long size(queue_t*);
//get the current max size of memory space that allocated
long mem_size(queue_t*);
//print queue to the std out: (1, ..., 20)
void out_q(queue_t*);

//Factory-functions:
//TODO threadsafe: create(mutex*)
//TODO initalise with specific size(it is the raise size too): create(int)
//Both: create(int, mutex*)
queue_t* create_thr(pthread_mutex_t*, long);

//TODO cut: give just a little view of the queue as a new queue pointer but it is still the same queue
queue_t** cutView(queue_t*, int);
queue_t* cutSingleView(queue_t*, long begin, long end);
#endif
