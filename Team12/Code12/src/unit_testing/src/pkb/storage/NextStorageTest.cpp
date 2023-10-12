#include <utility>
#include <vector>
#include <catch.hpp>

#include "common/AliasTypes.h"
#include "common/utils/PairUtils.h"
#include "pkb/storage/relation_storage/stmt_to_stmt/NextStorage.h"

using std::vector, std::pair;

void addNextRelationships(NextStorage& storage, IntToIntSetMap& map) {
  for (const auto& [from, toSet] : map) {
    for (int to : toSet) {
      storage.addNext(from, to);
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
void testIntSetEquality(const std::unordered_map<int, IntSet>& data,
                        Func getStmts) {
  for (const auto& [key, expectedSet] : data) {
    IntSet actual = getStmts(key);
    REQUIRE(actual == expectedSet);
  }
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

TEST_CASE("NextStorage - 1 proc") {
  NextStorage storage;
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

  SECTION("getNextStmts") {
    testIntSetEquality(nextStmts,
                       [&](int from) { return storage.getNextStmts(from); });
    REQUIRE(storage.getNextStmts(8).empty());
  }

  SECTION("getNextTStmts") {
    testIntSetEquality(expectedNextTStmts,
                       [&](int from) { return storage.getNextTStmts(from); });
    REQUIRE(storage.getNextTStmts(8).empty());
  }

  SECTION("getPrevStmts") {
    testIntSetEquality(prevStmts,
                       [&](int to) { return storage.getPrevStmts(to); });
    REQUIRE(storage.getPrevStmts(1).empty());
  }

  SECTION("getPrevTStmts") {
    testIntSetEquality(expectedPrevTStmts,
                       [&](int to) { return storage.getPrevTStmts(to); });
    REQUIRE(storage.getPrevTStmts(1).empty());
  }

  SECTION("isNext") {
    testNestedIntSets(
        nextStmts, [&](int from, int to) { return storage.isNext(from, to); });
    REQUIRE(!storage.isNext(1, 3));
    REQUIRE(!storage.isNext(6, 8));
  }

  SECTION("isNextT") {
    testNestedIntSets(expectedNextTStmts, [&](int from, int to) {
      return storage.isNextT(from, to);
    });
    REQUIRE(!storage.isNextT(5, 6));
    REQUIRE(!storage.isNextT(5, 7));
    REQUIRE(!storage.isNextT(7, 1));
    REQUIRE(!storage.isNextT(8, 8));
  }

  SECTION("getNextPairs") {
    std::unordered_set<pair<int, int>, PairUtils::PairHash> expected =
        getExpectedNextPairs(nextStmts);
    vector<pair<int, int>> actual = storage.getNextPairs();
    std::unordered_set<pair<int, int>, PairUtils::PairHash> actualSet(
        actual.begin(), actual.end());
    REQUIRE(actualSet == expected);
  }
}

TEST_CASE("NextStorage - multiple procs") {
  NextStorage storage;
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

  SECTION("getNextStmts") {
    testIntSetEquality(nextStmts,
                       [&](int from) { return storage.getNextStmts(from); });
    REQUIRE(storage.getNextStmts(3).empty());
    REQUIRE(storage.getNextStmts(9).empty());
  }

  SECTION("getNextTStmts") {
    testIntSetEquality(expectedNextTStmts,
                       [&](int from) { return storage.getNextTStmts(from); });
    REQUIRE(storage.getNextStmts(3).empty());
    REQUIRE(storage.getNextStmts(9).empty());
  }

  SECTION("getPrevStmts") {
    testIntSetEquality(prevStmts,
                       [&](int to) { return storage.getPrevStmts(to); });
    REQUIRE(storage.getPrevStmts(1).empty());
  }

  SECTION("getPrevTStmts") {
    testIntSetEquality(expectedPrevTStmts,
                       [&](int to) { return storage.getPrevTStmts(to); });
    REQUIRE(storage.getPrevTStmts(1).empty());
  }

  SECTION("isNext") {
    testNestedIntSets(
        nextStmts, [&](int from, int to) { return storage.isNext(from, to); });
    REQUIRE(!storage.isNext(1, 3));
    REQUIRE(!storage.isNext(6, 8));
  }

  SECTION("isNextT") {
    testNestedIntSets(expectedNextTStmts, [&](int from, int to) {
      return storage.isNextT(from, to);
    });
    REQUIRE(!storage.isNextT(5, 7));
    REQUIRE(!storage.isNextT(5, 8));
    REQUIRE(!storage.isNextT(7, 1));
    REQUIRE(!storage.isNextT(8, 8));
  }

  SECTION("getNextPairs") {
    std::unordered_set<pair<int, int>, PairUtils::PairHash> expected =
        getExpectedNextPairs(nextStmts);
    vector<pair<int, int>> actual = storage.getNextPairs();
    std::unordered_set<pair<int, int>, PairUtils::PairHash> actualSet(
        actual.begin(), actual.end());
    REQUIRE(actualSet == expected);
  }
}
