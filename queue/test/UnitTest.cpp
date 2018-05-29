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

