// TEMP_CATCH_INCLUDE

#include "../../../../spa/src/pkb/storage/ParentStorage.h"

TEST_CASE("ParentStorage Tests") {
  ParentStorage storage;

  storage.setParent(1, 2);
  storage.setParent(1, 3);
  storage.setParent(3, 4);
  storage.setParent(3, 5);
  storage.setParentStar(1, 2);
  storage.setParentStar(1, 3);
  storage.setParentStar(1, 4);
  storage.setParentStar(1, 5);
  storage.setParentStar(3, 4);
  storage.setParentStar(3, 5);

  SECTION("Setting and Getting Parent Relationship") {
    REQUIRE(storage.getAllParents(1) == std::set<int>{});
    REQUIRE(storage.getAllParents(2) == std::set<int>{1});
    REQUIRE(storage.getAllParents(3) == std::set<int>{1});
    REQUIRE(storage.getAllParents(4) == std::set<int>{1, 3});
    REQUIRE(storage.getAllParents(5) == std::set<int>{1, 3});
  }

  SECTION("Test getAllChildren") {
    REQUIRE(storage.getAllChildren(1) == std::set<int>{2, 3, 4, 5});
    REQUIRE(storage.getAllChildren(2) == std::set<int>{});
    REQUIRE(storage.getAllChildren(3) == std::set<int>{4, 5});
    REQUIRE(storage.getAllChildren(4) == std::set<int>{});
    REQUIRE(storage.getAllChildren(5) == std::set<int>{});
  }

  SECTION("Test getImmediateParent") {
    REQUIRE(storage.getImmediateParent(1) == -1);
    REQUIRE(storage.getImmediateParent(2) == 1);
    REQUIRE(storage.getImmediateParent(3) == 1);
    REQUIRE(storage.getImmediateParent(4) == 3);
    REQUIRE(storage.getImmediateParent(5) == 3);
  }

  SECTION("Test getImmediateChildren") {
    REQUIRE(storage.getImmediateChildren(1) == std::set<int>{2, 3});
    REQUIRE(storage.getImmediateChildren(2) == std::set<int>{});
    REQUIRE(storage.getImmediateChildren(3) == std::set<int>{4, 5});
    REQUIRE(storage.getImmediateChildren(4) == std::set<int>{});
    REQUIRE(storage.getImmediateChildren(5) == std::set<int>{});
  }

  SECTION("Getting All Parents and Children") {
    REQUIRE(storage.getAllParents() == std::set<int>{1, 3});
    REQUIRE(storage.getAllChildren() == std::set<int>{2, 3, 4, 5});
  }
}
