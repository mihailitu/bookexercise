#include "gtest.h"

#include "expressions.h"

TEST(Fundamentals, Expressions)
{
    std::string expr = "( 1 + 2 * ( 3 + 4 ) )";
    int result = eval<int>(expr);
    ASSERT_EQ(result, 15);
}
