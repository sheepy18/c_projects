#include "queue.h"

queue_t* create() {
   queue_t* newq = (queue_t*) malloc(sizeof(queue_t)); 
   newq->s = 10;
   newq->ce = 0;
   newq->q = malloc(sizeof(TYPE) * newq->s);
   return newq;
}

void push(queue_t* q_arg, TYPE e) {
    if(q_arg->s == q_arg->ce) 
       return;
    q_arg->q[q_arg->ce] = e;
    (q_arg->ce)++;
}


TYPE get(queue_t* q_arg) {
    return q_arg->q[0];
}

void out_q(queue_t* q_arg){
    printf("q:(");
    for(int i = 0; i < q_arg->ce - 1; i++)
        printf("%li,",q_arg->q[i]);
    printf("%li)\n", q_arg->q[q_arg->ce -1]);
}
