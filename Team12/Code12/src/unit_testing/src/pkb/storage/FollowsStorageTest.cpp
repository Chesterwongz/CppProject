#include <catch.hpp>

#include "pkb/storage/relation_storage/stmt_to_stmt/FollowsStorage.h"

TEST_CASE("FollowsStorage Tests") {
  FollowsStorage storage;

  storage.setFollows(1, 2);
  storage.setFollows(1, 3);
  storage.setFollows(2, 3);

  SECTION("Test setFollows and getAllFollows") {
    REQUIRE(storage.getAllFollows(1) == std::set<int>{2, 3});
    REQUIRE(storage.getAllFollows(2) == std::set<int>{3});
    REQUIRE(storage.getAllFollows(3).empty());
  }

  SECTION("Test getAllFollowedBy") {
    REQUIRE(storage.getAllFollowedBy(3) == std::set<int>{1, 2});
    REQUIRE(storage.getAllFollowedBy(1).empty());
  }

  SECTION("Test getImmediateFollows") {
    REQUIRE(storage.getImmediateFollows(1) == 2);
    REQUIRE(storage.getImmediateFollows(3) == -1);
  }

  SECTION("Test getImmediateFollowedBy") {
    REQUIRE(storage.getImmediateFollowedBy(3) == 2);
    REQUIRE(storage.getImmediateFollowedBy(1) == -1);
  }
}
