#include <stdio.h>
#include "queue.h"

int main() {
	queue_t* q1 = create();
    for(int i = 0; i < 10; i++)
        push(q1, q1->ce);
   
    printf("q1 size: %li \n", q1->s);
    printf("q1 get: %li \n", get(q1));
	printf("q1 ce: %li \n", q1->ce);
    printf("q1[ce]: %li \n", q1->q[q1->ce-1]);
    out_q(q1);
    return 0;
}
