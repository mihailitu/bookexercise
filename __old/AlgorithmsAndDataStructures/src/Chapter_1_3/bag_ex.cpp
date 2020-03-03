#include "fundamentals.h"
#include "bag_impl.h"

TEST(Fundamentals, BagExamle)
{
    bag<int> b;
    unsigned bagSz = 10;
    for(unsigned i = 0; i < bagSz; ++i)
        b.add(static_cast<int>(i));

    ASSERT_EQ(b.size(), bagSz);
    ASSERT_TRUE(b.exists(5));
    ASSERT_TRUE(b.exists(7));

    b.remove(5);
    b.remove(7);
    ASSERT_EQ(b.size(), bagSz - 2);

    ASSERT_FALSE(b.exists(5));
    ASSERT_FALSE(b.exists(7));
}
