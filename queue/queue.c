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
    //startpointer of the memory
    long start;
    //actual data
    TYPE* q;
};

queue_t* create(long size) {
   queue_t* newq = (queue_t*) malloc(sizeof(queue_t)); 
   newq->s = size;
   newq->ce = 0;
   newq->q = malloc(sizeof(TYPE) * newq->s);
   newq->start = 0;
   return newq;
}

queue_t* create_thr(pthread_mutex_t* m, long size) {
    pthread_mutex_lock(m);
    queue_t* newq = create(size);
    newq->mtx = m;
    pthread_mutex_unlock(m);
    return newq;
}

void increment_mem(queue_t* q_arg) {
    q_arg->s +=  (q_arg->s*1.5);
}

//not thread safe
void increment(queue_t* q_arg){
    (q_arg->ce)++;
}

//not thread safe
void decrement(queue_t* q_arg) {
    (q_arg->ce)--;
}

void allocMem(queue_t* q_arg, int isPop) {  
    TYPE* oldMem;
    if(!isPop) {
        oldMem = realloc(q_arg->q, q_arg->s);
        if(!oldMem)
            printf("ERROR: Realloc failed in line 47!\n");
        else
            q_arg->q = oldMem;
        return;
    }
    oldMem = q_arg->q;
    for(int i = 0; i < q_arg->ce; i++) {
       q_arg->q[i] = oldMem[i + 1]; 
    }
}

int pop(queue_t* q_arg) {

    if(size(q_arg) == 0) 
        return E_POP;
    if(q_arg->mtx == NULL){
        return E_POP;
    }
    pthread_mutex_lock(q_arg->mtx); 
    decrement(q_arg);
    (q_arg->start)++;
//    allocMem(q_arg, 1);
    pthread_mutex_unlock(q_arg->mtx);
    return SUCCESS;
}

int push(queue_t* q_arg, TYPE e) {
    if(q_arg->mtx == NULL){
        return E_PUSH;
    }
    pthread_mutex_lock(q_arg->mtx);
    if(q_arg->s == q_arg->ce) {  
   //     increment_mem(q_arg); 
 //       allocMem(q_arg, 0);
        pthread_mutex_unlock(q_arg->mtx);
        return E_PUSH;
    }

    q_arg->q[q_arg->ce % q_arg->s] = e;
    increment(q_arg);
    pthread_mutex_unlock(q_arg->mtx);
    return SUCCESS;
}

long size(queue_t* q) {
    if(q->mtx == NULL){
        return E_SIZE;
    }
    pthread_mutex_lock(q->mtx);
    long size = q->ce;
    pthread_mutex_unlock(q->mtx);
    return size;
}

long mem_size(queue_t* q ) {
    if(q->mtx == NULL){
        return E_SIZE;
    }
    pthread_mutex_lock(q->mtx);
    long mem = q->s;
    pthread_mutex_unlock(q->mtx);
    return mem;
}
TYPE get(queue_t* q_arg) {
    if(q_arg->mtx == NULL){
        return E_GET;
    }
    if(size(q_arg) == 0)
        return E_GET;

    pthread_mutex_lock(q_arg->mtx);
    TYPE first = q_arg->q[(q_arg->start) % (q_arg->s)];
    pthread_mutex_unlock(q_arg->mtx);
    return first;
}

queue_t** cutView(queue_t* q_arg,int views_num){
    if(views_num == 0) {
        return NULL;
    }
    queue_t** views = malloc(sizeof(queue_t*) * views_num);
    long current = 0;
    long part = ((q_arg->ce) / views_num);
    long rest = (q_arg->ce) % views_num;
    for(int i = 0; i < views_num; i++) {
        views[i] = cutSingleView(q_arg, current, current + ((i < rest)? part + 1 : part));
        current += part;
    
    }

    return views;
}

queue_t* cutSingleView(queue_t* q_arg, long begin, long end) {
    if((end - begin) > q_arg->ce) {
        return NULL;
    }

    pthread_mutex_t * m = malloc(sizeof(pthread_mutex_t));
    
    queue_t* newQ = malloc(sizeof(queue_t));
    newQ->q = (q_arg->q) + ((begin + q_arg->start) % q_arg->s);
    newQ->ce = (end - begin);
    newQ->s = end - begin;
    newQ->mtx = m;
    newQ->start = 0;
    return newQ;
}


void out_q(queue_t* q_arg){
    if(size(q_arg) == 0) return;  
    pthread_mutex_lock(q_arg->mtx);
    printf("q:(");
    if(q_arg->ce == 0) {    
        printf(")\n");
        pthread_mutex_unlock(q_arg->mtx); 
        return;
    }
    for(int i = 0; i < q_arg->ce - 1; i++)
        printf("%li,",q_arg->q[(i + q_arg->start) % q_arg->s]);
    printf("%li)\n", q_arg->q[(q_arg->start + q_arg->ce -1)% q_arg->s]);
    pthread_mutex_unlock(q_arg->mtx);
}
