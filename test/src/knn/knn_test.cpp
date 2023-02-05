#include <vector>
#include "knn/knn.hpp"
#include "CppUTest/TestHarness.h"

using namespace knn;
using namespace std;

TEST_GROUP(knn){};

TEST(knn, should_do_the_thing)
{
  enum class Class {
    a,
    b,
    c
  };

  auto neighbors = vector{
    make_pair(Class::a, 3),
    make_pair(Class::b, 1),
    make_pair(Class::b, 2),
    make_pair(Class::a, 5),
    make_pair(Class::c, 0),
    make_pair(Class::c, 5),
    make_pair(Class::c, 6),
  };

  Class actual = knn::classify(
    1,
    3,
    neighbors.begin(),
    neighbors.end(),
    [](const auto& lhs, const auto& rhs) {
      return abs(lhs - rhs);
    });

  CHECK(Class::b == actual);
}
