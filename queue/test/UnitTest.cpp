#include "UnitTest.hh"

CPPUNIT_TEST_SUITE_REGISTRATION( UnitTest );

void UnitTest::testConstructor()
{


    CPPUNIT_ASSERT( size(q) == 0 );
    CPPUNIT_ASSERT( mem_size(q) == 10 );

}

void UnitTest::setUp()
{
    pthread_mutex_init(&m, NULL);
   
    q = create_thr(&m, 10);
}

void UnitTest::tearDown()
{
    free(q);
}

void UnitTest::testOnePushOnePop()
{
    int v = 7;
    push(q, &v);
    v =*((int*) get(q));
    
    CPPUNIT_ASSERT_EQUAL( 7, v );
    CPPUNIT_ASSERT_EQUAL( 1L ,  size(q) );
    CPPUNIT_ASSERT_EQUAL( 10L, mem_size(q) );

    pop(q);

    CPPUNIT_ASSERT( E_GET == get(q) );
    CPPUNIT_ASSERT_EQUAL( 0L ,  size(q) );
    CPPUNIT_ASSERT_EQUAL( 10L, mem_size(q) );
}

void UnitTest::testTenPushElevenPop()
{
    int v[10];
    int g = 0;
    for(int i = 0; i < 10; i++)
        v[i] = i + 1;

    for(int i = 0; i < 10; i++)
        push(q, &v[i]);



    CPPUNIT_ASSERT_EQUAL(10L, size(q));
    g = *((int*) get(q));
    CPPUNIT_ASSERT_EQUAL(1, g);
    for(int i = 0; i < 10; i++)
        pop(q);


    CPPUNIT_ASSERT_EQUAL( 0L, size(q) );
    CPPUNIT_ASSERT( get(q) == E_GET );

    CPPUNIT_ASSERT(pop(q) == E_POP);

    CPPUNIT_ASSERT_EQUAL( 0L, size(q) );
    CPPUNIT_ASSERT( get(q) == E_GET );

}


void UnitTest::testPushAndPopMemoryRing() 
{
    q = create_thr(&m, 2);
    int v[5];
    int g = 0;
    
    for(int i = 0; i < 5; i++){
        v[i] = i + 1;
        push(q, &v[i]);
    }

    CPPUNIT_ASSERT_EQUAL(2L, size(q));
    g = *((int*) get(q));
    CPPUNIT_ASSERT_EQUAL(1, g);
    
    for(int i = 0; i < 2; i++) {
        pop(q);
    }
   
    CPPUNIT_ASSERT_EQUAL(0L, size(q));
    CPPUNIT_ASSERT(get(q) == E_GET);
   
    push(q, &v[3]);
    push(q, &v[4]);

    CPPUNIT_ASSERT_EQUAL(2L, size(q));
    g = *((int*) get(q));
    CPPUNIT_ASSERT_EQUAL(4, g);
    
    
    CPPUNIT_ASSERT(push(q, &v[1]) == E_PUSH);

}



void UnitTest::testCutSingleViewEmptyQueue()
{
   queue_t* cuttedQueue = cutSingleView( q, 0 , 1 );
   CPPUNIT_ASSERT(get(cuttedQueue) == E_GET);
}
void UnitTest::testCutSingleViewPop()
{
    CPPUNIT_FAIL("not implemented!");
}
void UnitTest::testCutSingleViewPush()
{
    CPPUNIT_FAIL("not implemented!");
}
void UnitTest::testCutViewEmptyQueue()
{
    CPPUNIT_FAIL("not implemented!");
}
void UnitTest::testCutView()
{
    CPPUNIT_FAIL("not implemented!");
}
