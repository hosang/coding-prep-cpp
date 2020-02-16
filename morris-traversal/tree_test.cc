#include "tree.h"

#include "absl/random/random.h"
#include "absl/algorithm/container.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

std::vector<int> RandomVector(int size) {
  absl::BitGen gen;
  std::vector<int> result;
  result.reserve(size);
  for (int i = 0; i < size; ++i) {
    result.push_back(absl::Uniform<int>(gen, -1000000, 1000000));
  }
  return result;
}

TEST(Tree, TestInsert) {
  Tree<int> t;
  t.Insert(3);
  t.Insert(1);
  t.Insert(4);
  t.Insert(2);

  std::vector<int> in_order;
  t.InOrder([&](int value) { in_order.push_back(value); });
  EXPECT_THAT(in_order, testing::ElementsAre(1, 2, 3, 4));
}

TEST(Tree, TestRandomInsert) {
  std::vector<int> data = RandomVector(10000);
  Tree<int> t;
  for (int i : data) {
    t.Insert(i);
  }
  
  absl::c_sort(data);
  std::vector<int> in_order;
  t.InOrder([&](int value) { in_order.push_back(value); });
  EXPECT_THAT(in_order, testing::ElementsAreArray(data));
}

TEST(Tree, TestRandomMorrisInOrder) {
  std::vector<int> data = RandomVector(10000);
  Tree<int> t;
  for (int i : data) {
    t.Insert(i);
  }
  
  absl::c_sort(data);
  std::vector<int> in_order;
  t.MorrisInOrder([&](int value) { in_order.push_back(value); });
  EXPECT_THAT(in_order, testing::ElementsAreArray(data));
  
  // Double check tree is still intact.
  std::vector<int> new_in_order;
  t.InOrder([&](int value) { new_in_order.push_back(value); });
  EXPECT_THAT(new_in_order, testing::ElementsAreArray(data));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}