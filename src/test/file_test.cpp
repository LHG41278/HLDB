#include "file.h"
#include <gtest/gtest.h>
using namespace hldb;

TEST(HelloTest, BasicAssertions)
{
    FileManipulator file;
    char            buf[5];

    EXPECT_EQ(file.PageReadAsync(1, buf), status_t::Normal);
}
