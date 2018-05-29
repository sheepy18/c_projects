#include <stdio.h>
#include <assert.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../queue.h"

void test_InitalQueue_DifferentSizes(int);
void test_pushOnePopOne();
void test_pushSixPopSeven();



pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv) {
 // Get the top level suite from the registry
  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

  // Adds the test to the list of test to run
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( suite );

  // Change the default outputter to a compiler error format outputter
  runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                                                       std::cerr ) );
  // Run the tests.
  bool wasSucessful = runner.run();

  // Return error code 1 if the one of test failed.
  return wasSucessful ? 0 : 1;
}

queue_t* initQueue(long mem) {
    return create_thr(&mtx, mem);
}

void test_InitalQueue(long mem) {
    queue_t* q = initQueue(mem);
    assert(mem_size(q) == mem);
}

void test_InitalQueue_DifferentSizes(int n) {
    for(int i = 0; i < n; i++) {
        test_InitalQueue(i);
    }
}

void test_pushOnePopOne() {
    queue_t* q = initQueue(1);
    int g = 10;

    push(q, &g);
    g = *((int*)( get(q)));

    assert(g == 10);
    assert(size(q) == 1);
    assert(mem_size(q) == 1);

    pop(q);
    assert(get(q) == E_GET);
    assert(size(q) == 0);
    assert(mem_size(q) == 1);
}

void test_pushSixPopSeven() {
    queue_t* q = initQueue(6);
    int n[10];
    int* v;

    for(int i = 0; i < 10; i++) {
        n[i] = i + 1;
    }

    push(q, &n[0]);
    v = (int*) get(q);
    assert(*v == 1);

    push(q, &n[1]);
    v = (int*) get(q);
    assert(*v == 1);

    push(q, &n[2]);
    v = (int*) get(q);
    assert(*v == 1);
    
    push(q, &n[3]);
    v = (int*) get(q);
    assert(*v == 1);

    push(q, &n[4]);
    v = (int*) get(q);
    assert(*v == 1);
   
    push(q, &n[5]);
    v = (int*) get(q);
    assert(*v == 1);
    
    pop(q);
    v = (int*) get(q);
    assert(*v == 2);
    
    pop(q);
    v = (int*) get(q);
    assert(*v == 3);

    pop(q);
    v = (int*) get(q);
    assert(*v == 4);

    pop(q);
    v = (int*) get(q);
    assert(*v == 5);

    pop(q);
    v = (int*) get(q);
    assert(*v == 6);

    pop(q);
    v =  (int*) get(q);
    assert(v == E_GET);

    assert(pop(q) == E_POP);
    v = (int*)get(q);
    assert(v == E_GET);

    assert(size(q) == 0);
    assert(mem_size(q) == 6);
}

