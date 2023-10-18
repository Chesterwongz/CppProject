#include <catch.hpp>
#include <utility>
#include <vector>

#include "common/AliasTypes.h"
#include "common/utils/PairUtils.h"
#include "pkb/storage/NextStore.h"

using std::vector, std::pair;

void addNextRelationships(NextStore& storage, IntToIntSetMap& map) {
  for (const auto& [from, toSet] : map) {
    for (int to : toSet) {
      storage.addRelation(from, to);
    }
  }
}

std::unordered_set<pair<int, int>, PairUtils::PairHash> getExpectedNextPairs(
    IntToIntSetMap& nextStmts) {
  std::unordered_set<pair<int, int>, PairUtils::PairHash> expected;
  for (const auto& [from, toSet] : nextStmts) {
    for (int to : toSet) {
      expected.insert({from, to});
    }
  }
  return expected;
}

// ai-gen start (gpt-4, 1)
template <typename Func>
bool testIntSetEquality(const std::unordered_map<int, IntSet>& data,
                        Func getStmts) {
  for (const auto& [key, expectedSet] : data) {
    IntSet actual = getStmts(key);
    if (actual != expectedSet) {
      REQUIRE(actual == expectedSet);
      return false;
    }
  }
  return true;
}

template <typename Func>
void testNestedIntSets(const std::unordered_map<int, IntSet>& data,
                       Func isNextOrT) {
  for (const auto& [key, innerSet] : data) {
    for (int innerKey : innerSet) {
      REQUIRE(isNextOrT(key, innerKey));
    }
  }
}
// ai-gen end

TEST_CASE("NextStore - 1 proc") {
  NextStore storage;
  IntToIntSetMap nextStmts = {{1, {2}}, {2, {3, 6}}, {3, {4, 5}}, {4, {3}},
                              {5, {8}}, {6, {7}},    {7, {8}}};
  IntToIntSetMap prevStmts = {{2, {1}}, {3, {2, 4}}, {4, {3}},   {5, {3}},
                              {6, {2}}, {7, {6}},    {8, {5, 7}}};
  IntToIntSetMap expectedNextTStmts = {{1, {2, 3, 6, 4, 5, 8, 7}},
                                       {2, {3, 6, 4, 5, 8, 7}},
                                       {3, {3, 4, 5, 8}},
                                       {4, {3, 4, 5, 8}},
                                       {5, {8}},
                                       {6, {7, 8}},
                                       {7, {8}}};
  IntToIntSetMap expectedPrevTStmts = {
      {2, {1}},
      {3, {1, 2, 3, 4}},
      {4, {1, 2, 3, 4}},
      {5, {1, 2, 3, 4}},
      {6, {1, 2}},
      {7, {1, 2, 6}},
      {8, {1, 2, 3, 4, 5, 6, 7}},
  };
  addNextRelationships(storage, nextStmts);
  storage.getRelationsT();

  SECTION("getDirectSuccessors") {
    REQUIRE(testIntSetEquality(nextStmts, [&](int from) {
      return storage.getDirectSuccessors(from);
    }));
    REQUIRE(!storage.hasDirectSuccessor(8));
  }

  SECTION("getSuccessorsT") {
    REQUIRE(testIntSetEquality(expectedNextTStmts, [&](int from) {
      return storage.getSuccessorsT(from);
    }));
    REQUIRE(!storage.hasSuccessorsT(8));
  }

  SECTION("getDirectAncestors") {
    REQUIRE(testIntSetEquality(
        prevStmts, [&](int to) { return storage.getDirectAncestors(to); }));
    REQUIRE(!storage.hasDirectAncestor(1));
  }

  SECTION("getAncestorsT") {
    REQUIRE(testIntSetEquality(expectedPrevTStmts, [&](int to) {
      if (storage.hasAncestorsT(to)) return storage.getAncestorsT(to);
    }));
    REQUIRE(!storage.hasAncestorsT(1));
  }

  SECTION("hasDirectRelation") {
    testNestedIntSets(nextStmts, [&](int from, int to) {
      return storage.hasDirectRelation(from, to);
    });
    REQUIRE(!storage.hasDirectRelation(1, 3));
    REQUIRE(!storage.hasDirectRelation(6, 8));
  }

  SECTION("hasRelationT") {
    testNestedIntSets(expectedNextTStmts, [&](int from, int to) {
      return storage.hasRelationT(from, to);
    });
    REQUIRE(!storage.hasRelationT(5, 6));
    REQUIRE(!storage.hasRelationT(5, 7));
    REQUIRE(!storage.hasRelationT(7, 1));
    REQUIRE(!storage.hasRelationT(8, 8));
  }

  SECTION("getAllDirectRelations") {
    std::unordered_set<pair<int, int>, PairUtils::PairHash> expected =
        getExpectedNextPairs(nextStmts);
    vector<pair<int, int>> actual = storage.getAllDirectRelations();
    std::unordered_set<pair<int, int>, PairUtils::PairHash> actualSet(
        actual.begin(), actual.end());
    REQUIRE(actualSet == expected);
  }
}

TEST_CASE("NextStore - multiple procs") {
  NextStore storage;
  IntToIntSetMap nextStmts = {{1, {2}},   {2, {3}},   {4, {5, 7}}, {5, {6}},
                              {6, {9}},   {7, {8}},   {8, {9}},    {10, {11}},
                              {13, {14}}, {14, {15}}, {16, {17}},  {18, {19}}};
  IntToIntSetMap expectedNextTStmts = {
      {1, {2, 3}}, {2, {3}},  {4, {5, 7, 6, 9, 8}}, {5, {6, 9}},    {6, {9}},
      {7, {8, 9}}, {8, {9}},  {10, {11}},           {13, {14, 15}}, {14, {15}},
      {16, {17}},  {18, {19}}};
  IntToIntSetMap expectedPrevTStmts = {{2, {1}},
                                       {3, {1, 2}},
                                       {5, {4}},
                                       {6, {4, 5}},
                                       {7, {4}},
                                       {8, {4, 7}},
                                       {9, {4, 5, 6, 7, 8}},
                                       {11, {10}},
                                       {14, {13}},
                                       {15, {13, 14}},
                                       {17, {16}},
                                       {19, {18}}};
  IntToIntSetMap prevStmts = {{2, {1}},   {3, {2}},   {5, {4}},    {6, {5}},
                              {7, {4}},   {8, {7}},   {9, {6, 8}}, {11, {10}},
                              {14, {13}}, {15, {14}}, {17, {16}},  {19, {18}}};

  addNextRelationships(storage, nextStmts);

  SECTION("getDirectSuccessors") {
    testIntSetEquality(
        nextStmts, [&](int from) { return storage.getDirectSuccessors(from); });
    REQUIRE(storage.getDirectSuccessors(3).empty());
    REQUIRE(storage.getDirectSuccessors(9).empty());
  }

  SECTION("getSuccessorsT") {
    testIntSetEquality(expectedNextTStmts,
                       [&](int from) { return storage.getSuccessorsT(from); });
    REQUIRE(storage.getDirectSuccessors(3).empty());
    REQUIRE(storage.getDirectSuccessors(9).empty());
  }

  SECTION("getDirectAncestors") {
    testIntSetEquality(prevStmts,
                       [&](int to) { return storage.getDirectAncestors(to); });
    REQUIRE(storage.getDirectAncestors(1).empty());
  }

  SECTION("getAncestorsT") {
    testIntSetEquality(expectedPrevTStmts,
                       [&](int to) { return storage.getAncestorsT(to); });
    REQUIRE(storage.getAncestorsT(1).empty());
  }

  SECTION("hasDirectRelation") {
    testNestedIntSets(nextStmts, [&](int from, int to) {
      return storage.hasDirectRelation(from, to);
    });
    REQUIRE(!storage.hasDirectRelation(1, 3));
    REQUIRE(!storage.hasDirectRelation(6, 8));
  }

  SECTION("hasRelationT") {
    testNestedIntSets(expectedNextTStmts, [&](int from, int to) {
      return storage.hasRelationT(from, to);
    });
    REQUIRE(!storage.hasRelationT(5, 7));
    REQUIRE(!storage.hasRelationT(5, 8));
    REQUIRE(!storage.hasRelationT(7, 1));
    REQUIRE(!storage.hasRelationT(8, 8));
  }

  SECTION("getAllDirectRelations") {
    std::unordered_set<pair<int, int>, PairUtils::PairHash> expected =
        getExpectedNextPairs(nextStmts);
    vector<pair<int, int>> actual = storage.getAllDirectRelations();
    std::unordered_set<pair<int, int>, PairUtils::PairHash> actualSet(
        actual.begin(), actual.end());
    REQUIRE(actualSet == expected);
  }
}
