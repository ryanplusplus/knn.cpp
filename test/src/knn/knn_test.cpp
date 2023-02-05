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
    b
  };

  auto neighbors = vector<pair<Class, int>>{
    make_pair(Class::a, 3),
    make_pair(Class::b, 1),
    make_pair(Class::b, 2),
    make_pair(Class::a, 5),
  };

  auto actual = knn::classify<Class>(neighbors, 2, 1, [](const int& lhs, const int& rhs) {
    return abs(lhs - rhs);
  });

  CHECK(Class::b == actual);
}
