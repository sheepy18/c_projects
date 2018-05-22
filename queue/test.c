#include <stdio.h>
#include "queue.h"

void* thread(void*);
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv) {
    if(argc == 1)
        return simple_test();
    long n = atoi(argv[1]);
    int p = atoi(argv[2]);
    if(n < 1 || p > 96 || p < 1) {
        printf("ERROR: arguments are not valid! choose: p < 96, p > 0, n > 0\n");
    }
    int e = tests(n, p);
    return 0;
}

int tests(long n, int p) {
    queue_t* q = create_thr(&m); 
    for(int i = 0; i < n; i++) {
        
    }

    return 0;
}


int simple_test() {
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
    printf("memSize: %li\n", mem_size(q1));   
    
    pthread_t thr[2];
 
  
    pthread_create(&thr[0],NULL, thread, q1); 
    pthread_create(&thr[1],NULL, thread, q1); 

    pthread_join(thr[0], NULL);
    pthread_join(thr[1], NULL);

    push(q1, (void*)(11));

    out_q(q1);
    printf("memSize: %li\n", mem_size(q1));   
    printf("size: %li \n", size(q1));
    return 0;
}


void* thread(void* arg) {
   pthread_mutex_lock(&m);
   queue_t* q = (queue_t*) arg;
   pthread_mutex_unlock(&m);

   for(int i = 0; i < 5; i++)
     push(q, (void*) (size(q)+1));
   return q;
}
