#ifndef UNITTEST_HH
#define UNITTEST_HH

#include <pthread.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../queue.h"


class UnitTest : public CppUnit::TestFixture 
{
    CPPUNIT_TEST_SUITE( UnitTest );
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testOnePushOnePop );
    CPPUNIT_TEST_SUITE_END();


    public:
        pthread_mutex_t m;
        queue_t* q;

        void testConstructor();
        void testOnePushOnePop();
        void setUp();
        void tearDown();


};



#endif
