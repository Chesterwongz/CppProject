#include <catch.hpp>

#include "sp/ast/TNode.h"
using namespace std;
void require(bool b) { REQUIRE(b); }

TEST_CASE("1st Test") { require(1 == 1); }
