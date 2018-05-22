#include <stdio.h>
#include "queue.h"

void* thread(void*);

int main() {
    pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	queue_t* q1 = create_thr(&m);
    printf("q1 size: %li \n", size(q1));
    for(int i = 0; i < 10; i++)
        push(q1,(void*) (i+1));
   
    printf("q1 get: %li \n", (long int) (get(q1)));
	printf("q1 size: %li \n", size(q1));
    printf("q1 mem_size: %li \n", mem_size(q1));
    out_q(q1);
    int s = size(q1);
    for(int i = 0; i < s; i++)
        pop(q1);

    printf("size: %li \n", size(q1));
    out_q(q1);
   
    
    pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
    pthread_t thr[2];
    queue_t* q2 = create_thr(&m2);
    out_q(q2);
    pthread_create(&thr[0],NULL, thread, q2); 
    pthread_create(&thr[1],NULL, thread, q2); 

    out_q(q2);
    return 0;
}


void* thread(void* arg) {
   queue_t* q = (queue_t*) arg;
   for(int i = 0; i < 5; i++)
     push(q, (void*) (i+2));
   return q;
}
