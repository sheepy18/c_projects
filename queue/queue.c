#include "queue.h"

//Queue with FIFO principle, and with thread safe possiblity
//struct: void* data, int size
struct q_t{
    //mutex for thread safety
     pthread_mutex_t *mtx;
    //current count of elements
    long ce;
    //beginning and raise size of queue
    long s; 
    //actual data
    TYPE* q;
};

queue_t* create() {
   queue_t* newq = (queue_t*) malloc(sizeof(queue_t)); 
   newq->s = 10;
   newq->ce = 0;
   newq->q = malloc(sizeof(TYPE) * newq->s);
   return newq;
}

queue_t* create_thr(pthread_mutex_t* m) {
    queue_t* newq = create();
    newq->mtx = m;
    return newq;
}

//TODO implementation of void pop() 


void push(queue_t* q_arg, TYPE e) {
    pthread_mutex_lock(q_arg->mtx);
    if(q_arg->s == q_arg->ce) {  
       pthread_mutex_unlock(q_arg->mtx);
       return;
    }

    q_arg->q[q_arg->ce] = e;
    (q_arg->ce)++;
    pthread_mutex_unlock(q_arg->mtx);
}

long size(queue_t* q) {
    pthread_mutex_lock(q->mtx);
    long size = q->ce;
    pthread_mutex_unlock(q->mtx);
    return size;
}

long mem_size(queue_t* q ) {
    pthread_mutex_lock(q->mtx);
    long mem = q->s;
    pthread_mutex_unlock(q->mtx);
    return mem;
}
TYPE get(queue_t* q_arg) {
    pthread_mutex_lock(q_arg->mtx);
    TYPE first = q_arg->q[0];
    pthread_mutex_unlock(q_arg->mtx);
    return first;
}

void print_q(queue_t* q) {
    pthread_mutex_lock(q->mtx);
    out_q(q);
    pthread_mutex_unlock(q->mtx);
}

void out_q(queue_t* q_arg){
    printf("q:(");
    for(int i = 0; i < q_arg->ce - 1; i++)
        printf("%li,",q_arg->q[i]);
    printf("%li)\n", q_arg->q[q_arg->ce -1]);
}
