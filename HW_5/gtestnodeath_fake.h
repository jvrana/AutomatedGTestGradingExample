// https://gist.github.com/DigitalInBlue/e9f143a8d1f6a6670995ff9fcaef9721 - 2018-02-18
// modified by Justin D Vrana - 2018-02-08

#ifndef ECE590_GTESTNODEATH_H
#define ECE590_GTESTNODEATH_H

#include <gtest/gtest.h>
#include <stdlib.h>

#define GTEST_COUT std::cerr             << "[    INFO  ] "
#define GTEST_COUT_ERROR std::cerr       << "[ SEGFAULT ] "

# define EXPECT_NO_DEATH(statement, regex)

# define EXPECT_NO_EXIT(statement, predicate, regex)

# define GTEST_NO_DEATH_TEST_(statement, predicate, regex, fail)


# define ASSERT_NO_EXIT(statement, predicate, regex) \
    GTEST_NO_DEATH_TEST_(statement, predicate, regex, GTEST_FATAL_FAILURE_)

#define ASSERT_NO_DEATH(statement, regex)

#endif //ECE590_GTESTNODEATH_H
