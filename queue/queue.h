#ifndef QUEUE_H
#define QUEUE_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define TYPE void*
//Queue with FIFO principle, and with thread safe possiblity
//struct: void* data, int size
typedef struct{
    //mutex for thread safety
     pthread_mutex_t *mtx;
    //current count of elements
    long ce;
    //beginning and raise size of queue
    long s; 
    //actual data
    TYPE* q;
} queue_t;

//pop: deletes the first element 
void pop(queue_t*);
//push: adds an element(e) at the end
void push(queue_t*, TYPE e);
//get: get the first element
TYPE get(queue_t*);
//size: get the current number of elements
long size(queue_t*);

//print queue to the std out: (1, ..., 20)
void out_q(queue_t*);

//Factory-functions:
//default: create()
queue_t* create(); 
//threadsafe: create(mutex*)
queue_t* create_thr(pthread_mutex_t*);
//initalise with specific size(it is the raise size too): create(int)
//Both: create(int, mutex*)
#endif
