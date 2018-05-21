#include <stdio.h>
#include "queue.h"

int main() {
    pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	queue_t* q1 = create_thr(&m);
    for(int i = 0; i < 10; i++)
        push(q1, q1->ce);
   
    printf("q1 size: %li \n", q1->s);
    printf("q1 get: %li \n", get(q1));
	printf("q1 ce: %li \n", q1->ce);
    printf("q1[ce]: %li \n", q1->q[q1->ce-1]);
    printf("q1 mem_size: %li \n", mem_size(q1));
    print_q(q1);
    return 0;
}
