#ifndef UNITTEST_HH
#define UNITTEST_HH

#include <pthread.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../queue.h"


class UnitTest : public CppUnit::TestFixture 
{
    CPPUNIT_TEST_SUITE( UnitTest );
    //every test runs in another TextFixture object
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testOnePushOnePop );
    CPPUNIT_TEST( testTenPushElevenPop );
    CPPUNIT_TEST( testPushAndPopMemoryRing );
    CPPUNIT_TEST( testCutSingleViewEmptyQueue );
  
    CPPUNIT_TEST_SUITE_END();


    public:
        pthread_mutex_t m;
        queue_t* q;

        //runs before every test
        void setUp();
        //runs after every test
        void tearDown();
        
        void testConstructor();
        void testOnePushOnePop();
        void testTenPushElevenPop();
        void testPushAndPopMemoryRing();
        void testCutSingleViewEmptyQueue();
        void testCutSingleViewPop();
        void testCutSingleViewPush();
        void testCutViewEmptyQueue();
        void testCutView();
};



#endif
