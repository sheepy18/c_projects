#include <stdio.h>
#include "queue.h"
pthread_mutex_t m;
int testsSequential(long);
int testsParallel(long, int);
int simple_test();
void* test_thr(void*);
int testsParallel(long, int);
void* thread(void*);
long sum = 0;

typedef struct {
    queue_t* q_t;
    long n_t;
} args;

int main(int argc, char** argv) {
    if(argc == 1)
        return simple_test();
    long n = atoi(argv[1]);
    int p = atoi(argv[2]);
    double speedup = 0;
    if(n < 1 || p > 96 || p < 1) {
        printf("ERROR: arguments are not valid! choose: p < 96, p > 0, n > 0\n");
        return 0;
    }
    double t0 = 0; //change to gettime()
    int e = testsSequential(n);
    double t1 = 1; //change to t0 - gettime()
    long seq_sum = sum;
    for(int i = 1; i <= p; i++) {
        sum = 0;
        t0 = 0; //change to gettime()
        e = testsParallel(n, i);
        double t2 = 1; //change to t0 - gettime()
        if(seq_sum != sum) {
            printf("ERROR: sequential sum: %li is not equal with parallel threads: %i sum: %li\n", seq_sum,i, sum);
            return 0;
        }
        speedup = t1 / t2;
        printf("sequential: %li, parallel: %li, threads %i, speedup: %lf\n", seq_sum, sum,i, speedup);
    }

    return e;
}

long calculate(int n, queue_t* q) {
    long sum_t = 0;
    for(int i = 0; i < n; i++) {
         sum_t += (long) get(q);
        if(pop(q) == E_POP) return 0;
    }
    return sum_t;
}

void initQueue(long n, queue_t* q) { 
    for(int i = 0; i < n; i++) {
        push(q, (void*)((long) (i + 1))); 
    }
}

int testsSequential(long n) {
    pthread_mutex_init(&m, NULL); 
    queue_t* q = create_thr(&m,n);
    initQueue(n, q);
    sum = calculate(n, q);
    pthread_mutex_destroy(&m);
    return 0;
}

int testsParallel(long n, int p) {
    args* a;
    pthread_mutex_init(&m, NULL);
    queue_t* q = create_thr(&m,n); 
    pthread_t thr[p];
    initQueue(n, q);
    
    for(int i = 0; i < p; i++) {
       a = malloc(sizeof(args));
       a->q_t = q;
       a->n_t = (n / p) + ((i < n % p)? 1 : 0 );
       pthread_create(&thr[i], NULL, test_thr, a); 
    }

    for(int i = 0; i < p; i++)
        pthread_join(thr[i], NULL);
    pthread_mutex_destroy(&m);
    return 0;
}


void* test_thr(void* arg) {
    args* a = (args*) arg;
    queue_t* q = a->q_t;
    long t = a->n_t;
    long sum_t = calculate(t, q);

    pthread_mutex_lock(&m);
    sum += sum_t;
    //printf("Thread sum: %li with n: %li\n", sum_t, t);
    pthread_mutex_unlock(&m);
   // free(a);
    return NULL;
}

int simple_test() {
	queue_t* q1 = create_thr(&m, 10);
    printf("q1 size: %li \n", size(q1));
    for(int i = 0; i < 10; i++)
        push(q1,(void*) ((long)(i+1)));
   
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
    int e = pop(q1);

    if(e == E_POP) {
        printf("ERROR in pop: %i\n", e);
    }

    void* get_e = get(q1);

    if(get_e == E_GET) {
        printf("ERROR in get: %i\n", get_e);
    }

    pthread_t thr[2];
 
  
    pthread_create(&thr[0],NULL, thread, q1); 
    pthread_create(&thr[1],NULL, thread, q1); 

    pthread_join(thr[0], NULL);
    pthread_join(thr[1], NULL);

    e = push(q1, (void*)(11));
    if(e == E_PUSH) printf("ERROR in push: %i\n", e);
    e = push(q1,(void*) 21);
    if(e == E_PUSH) printf("ERROR in push: %i\n", e);

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
