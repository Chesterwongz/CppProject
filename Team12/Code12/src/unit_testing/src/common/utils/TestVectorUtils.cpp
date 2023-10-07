// TEMP_CATCH_INCLUDE
#include <vector>

#include "common/utils/VectorUtils.h"

using std::string, std::vector;

vector<string> vector1 = {"0", "1", "banana",  "cat",
                          "2", "3", "lettuce", "pineapple"};
vector<string> vector2 = {"4", "5", "pear", "dog", "6", "7", "meow", "woof"};
vector<string> vector3 = {"0", "1", "potato"};

vector<string> VECTOR_1_INTERSECT_2 = {};
vector<string> VECTOR_1_INTERSECT_3 = {"0", "1"};

vector<string> VECTOR_1_CONCAT_2 = {
    "0", "1", "banana", "cat", "2", "3", "lettuce", "pineapple",
    "4", "5", "pear",   "dog", "6", "7", "meow",    "woof"};
vector<string> VECTOR_1_CONCAT_3 = {"0", "1", "banana",  "cat",
                                    "2", "3", "lettuce", "pineapple",
                                    "0", "1", "potato"};

TEST_CASE("Vector utils concat") {
  REQUIRE(concatVectors(vector1, vector2) == VECTOR_1_CONCAT_2);
  REQUIRE(concatVectors(vector1, vector3) == VECTOR_1_CONCAT_3);
}

TEST_CASE("Vector utils intersect") {
  REQUIRE(intersectVectors(vector1, vector2) == VECTOR_1_INTERSECT_2);
  REQUIRE(intersectVectors(vector1, vector3) == VECTOR_1_INTERSECT_3);
}
