//
// Created by Justin Vrana on 2019-02-04.
//

#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "gtest/gtest.h"
#include <stdlib.h>
#include "gtestnodeath.h"


void segfault()
{
    int * p = NULL;
    *p = 4;
}

void nosegfault()
{
    int * p = NULL;
}

// this should seg fault, but simply fail the test instead of crashing the program
TEST(SegFault,ShouldSegFaultAndFail)
{
    ASSERT_NO_DEATH(segfault(), ".*");
    std::cout << "This was supposed to fail!" << std::endl;
}

// this should pass
TEST(SegFault,ShouldNotSegFaultAndPass)
{
    ASSERT_NO_DEATH(nosegfault(), ".*");
}

// this should fail because of the nested assertion is false
TEST(SegFault,NestedAssertionShouldFail)
{
    int i = 0;
    ASSERT_NO_DEATH(
            i = 1
            , ".*");
    std::cout << "[     FAIL ] This nested assertion was supposed to fail!" << std::endl;
    ASSERT_EQ(i, 1);
}

// this should seg fault and we should be able to catch it
TEST(SegFault,ShouldSegFaultAndPass)
{
    ASSERT_EXIT((segfault(),exit(0)),::testing::KilledBySignal(SIGSEGV),".*");
}