#include <stdio.h>
#include "queue.h"

int main() {
    pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	queue_t* q1 = create_thr(&m);
    printf("q1 size: %li \n", size(q1));
    for(int i = 0; i < 10; i++)
        push(q1,(void*) (i+1));
   
    printf("q1 get: %li \n", (long int) (get(q1)));
	printf("q1 size: %li \n", size(q1));
    printf("q1 mem_size: %li \n", mem_size(q1));
    print_q(q1);
    return 0;
}
