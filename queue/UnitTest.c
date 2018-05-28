#include <stdio.h>
#include <assert.h>
#include "queue.h"

void test_InitalQueue_DifferentSizes(int);



int main(int argc, char** argv) {
    test_InitalQueue_DifferentSizes(20);
   
    printf("Unit test was successful!\n"); 
    return 0;
}

void test_InitalQueue(long mem) {
    pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
    queue_t* q = create_thr(&mtx, mem);
    assert(mem_size(q) == mem);
}

void test_InitalQueue_DifferentSizes(int n) {
    for(int i = 0; i < n; i++) {
        test_InitalQueue(i);
    }
}
