#include "skiplist.h"
#include <gtest/gtest.h>

TEST(SkipListTest, BasicTest) {
  auto IntComparator = [](const int &lhs ,const int &rhs){
    if (lhs > rhs) {
      return 1;
    } else if (lhs == rhs) {
      return 0;
    } else {
      return -1;
    }
  };
  hldb::SkipList<int ,int, decltype(IntComparator)> skiplist(IntComparator);

  hldb::status_t stat;

  stat = skiplist.Insert(7,1);
  ASSERT_EQ(stat, hldb::status_t::Normal);
  skiplist.Print();
  stat = skiplist.Insert(3,9);
  skiplist.Print();
  ASSERT_EQ(stat, hldb::status_t::Normal);
  stat = skiplist.Insert(6,1);
  skiplist.Print();
  ASSERT_EQ(stat, hldb::status_t::Normal);
  stat = skiplist.Insert(4,2);
  skiplist.Print();
  ASSERT_EQ(stat, hldb::status_t::Normal);
}