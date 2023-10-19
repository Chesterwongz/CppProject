#include <vector>
#include <catch.hpp>

#include "common/utils/CollectionUtils.h"

using std::string, std::vector;

vector<string> testVector1 = {"0", "1", "banana",  "cat",
                              "2", "3", "lettuce", "pineapple"};
vector<string> testVector2 = {"4", "5", "pear", "dog",
                              "6", "7", "meow", "woof"};
vector<string> testVector3 = {"0", "1", "potato"};

vector<string> VECTOR_1_INTERSECT_2 = {};
vector<string> VECTOR_1_INTERSECT_3 = {"0", "1"};

TEST_CASE("Vector utils intersect") {
  REQUIRE(CollectionUtils::intersectVectors(testVector1, testVector2) ==
          VECTOR_1_INTERSECT_2);
  REQUIRE(CollectionUtils::intersectVectors(testVector1, testVector3) ==
          VECTOR_1_INTERSECT_3);
}
