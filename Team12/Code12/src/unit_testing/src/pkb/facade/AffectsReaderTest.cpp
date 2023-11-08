#include <unordered_set>
#include <catch.hpp>

#include "../../common/utils/HelperFunctions.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/AffectsReader.h"

TEST_CASE("AffectsReader Tests 1") {
  AffectsCache affectsCache;
  ModifiesSStore modifiesSStore;
  NextStore nextStore;
  StmtStore stmtStore;
  UsesSStore usesSStore;

  stmtStore.addStmt(1, StmtType::ASSIGN);
  stmtStore.addStmt(2, StmtType::ASSIGN);
  stmtStore.addStmt(3, StmtType::WHILE);
  stmtStore.addStmt(4, StmtType::ASSIGN);
  stmtStore.addStmt(5, StmtType::CALL);
  stmtStore.addStmt(6, StmtType::ASSIGN);
  stmtStore.addStmt(7, StmtType::IF);
  stmtStore.addStmt(8, StmtType::ASSIGN);
  stmtStore.addStmt(9, StmtType::ASSIGN);
  stmtStore.addStmt(10, StmtType::ASSIGN);
  stmtStore.addStmt(11, StmtType::ASSIGN);
  stmtStore.addStmt(12, StmtType::ASSIGN);

  modifiesSStore.addRelation(1, "x");
  modifiesSStore.addRelation(2, "i");
  modifiesSStore.addRelation(4, "x");
  modifiesSStore.addRelation(6, "i");
  modifiesSStore.addRelation(8, "x");
  modifiesSStore.addRelation(9, "z");
  modifiesSStore.addRelation(10, "z");
  modifiesSStore.addRelation(11, "y");
  modifiesSStore.addRelation(12, "x");
  modifiesSStore.addRelation(5, "z");
  modifiesSStore.addRelation(5, "v");

  usesSStore.addRelation(4, "x");
  usesSStore.addRelation(4, "y");
  usesSStore.addRelation(6, "i");
  usesSStore.addRelation(8, "x");
  usesSStore.addRelation(10, "i");
  usesSStore.addRelation(10, "x");
  usesSStore.addRelation(10, "z");
  usesSStore.addRelation(11, "z");
  usesSStore.addRelation(12, "x");
  usesSStore.addRelation(12, "y");
  usesSStore.addRelation(12, "z");

  nextStore.addRelation(1, 2);
  nextStore.addRelation(2, 3);
  nextStore.addRelation(3, 4);
  nextStore.addRelation(3, 7);
  nextStore.addRelation(4, 5);
  nextStore.addRelation(5, 6);
  nextStore.addRelation(6, 3);
  nextStore.addRelation(7, 8);
  nextStore.addRelation(7, 9);
  nextStore.addRelation(8, 10);
  nextStore.addRelation(9, 10);
  nextStore.addRelation(10, 11);
  nextStore.addRelation(11, 12);

  SECTION("AffectsPairs") {
    AffectsReader affectsReader(affectsCache, modifiesSStore, nextStore,
                                stmtStore, usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(compareVectorContents(
        result,
        std::vector<std::pair<std::string, std::string>> {{"1", "4"},
                                                          {"1", "8"},
                                                          {"1", "10"},
                                                          {"1", "12"},
                                                          {"2", "6"},
                                                          {"2", "10"},
                                                          {"4", "4"},
                                                          {"4", "8"},
                                                          {"4", "10"},
                                                          {"4", "12"},
                                                          {"6", "6"},
                                                          {"6", "10"},
                                                          {"8", "10"},
                                                          {"8", "12"},
                                                          {"9", "10"},
                                                          {"10", "11"},
                                                          {"10", "12"},
                                                          {"11", "12"}}));
    REQUIRE(
        compareVectorContents(affectsReader.getAffects(1, StmtType::ASSIGN),
                              std::vector<std::string> {"4", "8", "10", "12"}));
    REQUIRE(
        compareVectorContents(affectsReader.getAffects(4, StmtType::ASSIGN),
                              std::vector<std::string> {"4", "8", "10", "12"}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(9, StmtType::ASSIGN),
                                  std::vector<std::string> {"10"}));
    REQUIRE(
        compareVectorContents(affectsReader.getAffects(12, StmtType::ASSIGN),
                              std::vector<std::string> {}));

    REQUIRE(compareVectorContents(
        affectsReader.getAffectedBy(12, StmtType::ASSIGN),
        std::vector<std::string> {"1", "4", "8", "10", "11"}));
    REQUIRE(
        compareVectorContents(affectsReader.getAffectedBy(6, StmtType::ASSIGN),
                              std::vector<std::string> {"2", "6"}));
    REQUIRE(
        compareVectorContents(affectsReader.getAffectedBy(1, StmtType::ASSIGN),
                              std::vector<std::string> {}));
    REQUIRE(affectsReader.isAffects(1, 4));
    REQUIRE(affectsReader.isAffects(4, 10));
    REQUIRE(affectsReader.isAffects(10, 11));
    REQUIRE(affectsReader.isAffects(11, 12));
    REQUIRE(affectsReader.isAffects(6, 6));
    REQUIRE(affectsReader.isAffects(1, 10));
    REQUIRE(affectsReader.isAffects(6, 10));
    REQUIRE_FALSE(affectsReader.isAffects(6, 11));
    REQUIRE_FALSE(affectsReader.isAffects(2, 11));
    REQUIRE_FALSE(affectsReader.isAffects(5, 11));
    REQUIRE_FALSE(affectsReader.isAffects(6, 2));
    REQUIRE_FALSE(affectsReader.isAffects(9, 11));
    REQUIRE_FALSE(affectsReader.isAffects(9, 12));
    REQUIRE_FALSE(affectsReader.isAffects(3, 8));
  }
}

TEST_CASE("AffectsReader Tests 2 - Code 7") {
  AffectsCache affectsCache;
  ModifiesSStore modifiesSStore;
  NextStore nextStore;
  StmtStore stmtStore;
  UsesSStore usesSStore;

  stmtStore.addStmt(1, StmtType::ASSIGN);
  stmtStore.addStmt(2, StmtType::IF);
  stmtStore.addStmt(3, StmtType::ASSIGN);
  stmtStore.addStmt(4, StmtType::ASSIGN);
  stmtStore.addStmt(5, StmtType::ASSIGN);

  modifiesSStore.addRelation(1, "x");
  modifiesSStore.addRelation(3, "x");
  modifiesSStore.addRelation(4, "a");
  modifiesSStore.addRelation(5, "a");

  usesSStore.addRelation(3, "a");
  usesSStore.addRelation(4, "b");
  usesSStore.addRelation(5, "x");

  nextStore.addRelation(1, 2);
  nextStore.addRelation(2, 3);
  nextStore.addRelation(2, 4);
  nextStore.addRelation(3, 5);
  nextStore.addRelation(4, 5);

  SECTION("AffectsPairs") {
    AffectsReader affectsReader(affectsCache, modifiesSStore, nextStore,
                                stmtStore, usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(compareVectorContents(
        result, std::vector<std::pair<std::string, std::string>> {{"1", "5"},
                                                                  {"3", "5"}}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(1, StmtType::ASSIGN),
                                  std::vector<std::string> {"5"}));
    REQUIRE(
        compareVectorContents(affectsReader.getAffectedBy(5, StmtType::ASSIGN),
                              std::vector<std::string> {"1", "3"}));
    REQUIRE(affectsReader.isAffects(1, 5));
    REQUIRE(affectsReader.isAffects(3, 5));
    REQUIRE_FALSE(affectsReader.isAffects(2, 4));
  }
}

TEST_CASE("AffectsReader Tests 3 - Code 8") {
  AffectsCache affectsCache;
  ModifiesSStore modifiesSStore;
  NextStore nextStore;
  StmtStore stmtStore;
  UsesSStore usesSStore;

  stmtStore.addStmt(1, StmtType::ASSIGN);
  stmtStore.addStmt(2, StmtType::CALL);
  stmtStore.addStmt(3, StmtType::ASSIGN);

  modifiesSStore.addRelation(1, "x");
  modifiesSStore.addRelation(3, "v");
  // If Modifies("q", "x") does not hold, then Affects(1, 3) holds.
  // modifiesSStore.addRelation("q", "x");

  usesSStore.addRelation(1, "a");
  usesSStore.addRelation(3, "x");

  nextStore.addRelation(1, 2);
  nextStore.addRelation(2, 3);

  SECTION("AffectsPairs") {
    AffectsReader affectsReader(affectsCache, modifiesSStore, nextStore,
                                stmtStore, usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(compareVectorContents(
        result, std::vector<std::pair<std::string, std::string>> {{"1", "3"}}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(1, StmtType::ASSIGN),
                                  std::vector<std::string> {"3"}));
    REQUIRE(
        compareVectorContents(affectsReader.getAffectedBy(3, StmtType::ASSIGN),
                              std::vector<std::string> {"1"}));
    REQUIRE(
        compareVectorContents(affectsReader.getAffectedBy(4, StmtType::ASSIGN),
                              std::vector<std::string> {}));
    REQUIRE(affectsReader.isAffects(1, 3));
    REQUIRE_FALSE(affectsReader.isAffects(3, 4));
  }
}

TEST_CASE("AffectsReader Tests 4 - Code 9") {
  AffectsCache affectsCache;
  ModifiesSStore modifiesSStore;
  NextStore nextStore;
  StmtStore stmtStore;
  UsesSStore usesSStore;

  stmtStore.addStmt(1, StmtType::ASSIGN);
  stmtStore.addStmt(2, StmtType::ASSIGN);
  stmtStore.addStmt(3, StmtType::ASSIGN);
  stmtStore.addStmt(4, StmtType::CALL);
  stmtStore.addStmt(5, StmtType::ASSIGN);
  stmtStore.addStmt(6, StmtType::ASSIGN);
  stmtStore.addStmt(7, StmtType::ASSIGN);
  stmtStore.addStmt(8, StmtType::IF);
  stmtStore.addStmt(9, StmtType::ASSIGN);
  stmtStore.addStmt(10, StmtType::ASSIGN);
  stmtStore.addStmt(11, StmtType::ASSIGN);

  modifiesSStore.addRelation(1, "x");
  modifiesSStore.addRelation(2, "y");
  modifiesSStore.addRelation(3, "z");
  modifiesSStore.addRelation(5, "z");
  modifiesSStore.addRelation(6, "x");
  modifiesSStore.addRelation(7, "t");
  modifiesSStore.addRelation(9, "t");
  modifiesSStore.addRelation(10, "y");
  modifiesSStore.addRelation(11, "x");
  modifiesSStore.addRelation(4, "x");
  modifiesSStore.addRelation(4, "t");
  modifiesSStore.addRelation(4, "y");

  usesSStore.addRelation(3, "y");
  usesSStore.addRelation(5, "x");
  usesSStore.addRelation(5, "y");
  usesSStore.addRelation(5, "z");
  usesSStore.addRelation(9, "x");
  usesSStore.addRelation(10, "x");
  usesSStore.addRelation(10, "z");
  usesSStore.addRelation(11, "t");
  usesSStore.addRelation(4, "x");
  usesSStore.addRelation(4, "z");
  usesSStore.addRelation(4, "t");

  nextStore.addRelation(1, 2);
  nextStore.addRelation(2, 3);
  nextStore.addRelation(3, 4);
  nextStore.addRelation(4, 5);
  nextStore.addRelation(6, 7);
  nextStore.addRelation(7, 8);
  nextStore.addRelation(8, 9);
  nextStore.addRelation(8, 10);
  nextStore.addRelation(9, 11);
  nextStore.addRelation(10, 11);

  SECTION("AffectsPairs") {
    AffectsReader affectsReader(affectsCache, modifiesSStore, nextStore,
                                stmtStore, usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(compareVectorContents(
        result,
        std::vector<std::pair<std::string, std::string>> {{"2", "3"},
                                                          {"3", "5"},
                                                          {"6", "9"},
                                                          {"6", "10"},
                                                          {"7", "11"},
                                                          {"9", "11"}}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(6, StmtType::ASSIGN),
                                  std::vector<std::string> {"9", "10"}));
    REQUIRE(
        compareVectorContents(affectsReader.getAffectedBy(11, StmtType::ASSIGN),
                              std::vector<std::string> {"7", "9"}));
    REQUIRE(affectsReader.isAffects(2, 3));
    REQUIRE(affectsReader.isAffects(7, 11));
    REQUIRE(affectsReader.isAffects(3, 5));
    REQUIRE(affectsReader.isAffects(6, 9));
    REQUIRE(affectsReader.isAffects(6, 10));
    REQUIRE(affectsReader.isAffects(9, 11));

    REQUIRE_FALSE(affectsReader.isAffects(6, 11));
    REQUIRE_FALSE(affectsReader.isAffects(1, 2));
    REQUIRE_FALSE(affectsReader.isAffects(4, 7));
    REQUIRE_FALSE(affectsReader.isAffects(5, 8));
    REQUIRE_FALSE(affectsReader.isAffects(7, 9));
    REQUIRE_FALSE(affectsReader.isAffects(10, 12));
    REQUIRE_FALSE(affectsReader.isAffects(1, 4));
    REQUIRE_FALSE(affectsReader.isAffects(1, 5));
    REQUIRE_FALSE(affectsReader.isAffects(1, 6));
    REQUIRE_FALSE(affectsReader.isAffects(1, 7));
    REQUIRE_FALSE(affectsReader.isAffects(1, 8));
    REQUIRE_FALSE(affectsReader.isAffects(1, 9));
    REQUIRE_FALSE(affectsReader.isAffects(1, 10));
    REQUIRE_FALSE(affectsReader.isAffects(1, 11));

    REQUIRE_FALSE(affectsReader.isAffects(2, 4));
    REQUIRE_FALSE(affectsReader.isAffects(2, 5));
    REQUIRE_FALSE(affectsReader.isAffects(2, 6));
    REQUIRE_FALSE(affectsReader.isAffects(2, 7));
    REQUIRE_FALSE(affectsReader.isAffects(2, 8));
    REQUIRE_FALSE(affectsReader.isAffects(2, 9));
    REQUIRE_FALSE(affectsReader.isAffects(2, 10));
    REQUIRE_FALSE(affectsReader.isAffects(2, 11));

    REQUIRE_FALSE(affectsReader.isAffects(3, 4));
    REQUIRE_FALSE(affectsReader.isAffects(3, 6));
    REQUIRE_FALSE(affectsReader.isAffects(3, 7));
  }
}

TEST_CASE("AffectsReader Tests 5 - Code 10") {
  AffectsCache affectsCache;
  ModifiesSStore modifiesSStore;
  NextStore nextStore;
  StmtStore stmtStore;
  UsesSStore usesSStore;

  stmtStore.addStmt(1, StmtType::ASSIGN);
  stmtStore.addStmt(2, StmtType::CALL);
  stmtStore.addStmt(3, StmtType::ASSIGN);
  stmtStore.addStmt(4, StmtType::IF);
  stmtStore.addStmt(5, StmtType::ASSIGN);
  stmtStore.addStmt(6, StmtType::ASSIGN);

  modifiesSStore.addRelation(1, "x");
  modifiesSStore.addRelation(3, "a");
  modifiesSStore.addRelation(5, "x");
  modifiesSStore.addRelation(6, "a");
  modifiesSStore.addRelation(2, "a");
  modifiesSStore.addRelation(2, "x");

  usesSStore.addRelation(3, "x");
  usesSStore.addRelation(5, "a");
  usesSStore.addRelation(6, "b");
  usesSStore.addRelation(2, "a");
  usesSStore.addRelation(2, "b");
  usesSStore.addRelation(2, "i");
  usesSStore.addRelation(4, "i");

  nextStore.addRelation(1, 2);
  nextStore.addRelation(2, 3);
  nextStore.addRelation(4, 5);
  nextStore.addRelation(4, 6);

  SECTION("AffectsPairs") {
    AffectsReader affectsReader(affectsCache, modifiesSStore, nextStore,
                                stmtStore, usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(compareVectorContents(
        result, std::vector<std::pair<std::string, std::string>> {}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(6, StmtType::ASSIGN),
                                  std::vector<std::string> {}));
    REQUIRE_FALSE(affectsReader.isAffects(1, 2));
  }
}

TEST_CASE("AffectsReader Tests 6 - Code 11") {
  AffectsCache affectsCache;
  ModifiesSStore modifiesSStore;
  NextStore nextStore;
  StmtStore stmtStore;
  UsesSStore usesSStore;

  stmtStore.addStmt(1, StmtType::ASSIGN);
  stmtStore.addStmt(2, StmtType::READ);
  stmtStore.addStmt(3, StmtType::ASSIGN);

  modifiesSStore.addRelation(1, "x");
  modifiesSStore.addRelation(2, "x");
  modifiesSStore.addRelation(3, "v");

  usesSStore.addRelation(1, "a");
  usesSStore.addRelation(3, "x");

  nextStore.addRelation(1, 2);
  nextStore.addRelation(2, 3);

  SECTION("AffectsPairs") {
    AffectsReader affectsReader(affectsCache, modifiesSStore, nextStore,
                                stmtStore, usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(compareVectorContents(
        result, std::vector<std::pair<std::string, std::string>> {}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(6, StmtType::ASSIGN),
                                  std::vector<std::string> {}));
    REQUIRE_FALSE(affectsReader.isAffects(2, 3));
  }
}

TEST_CASE("AffectsReader Tests 7 - Autotester") {
  AffectsCache affectsCache;
  ModifiesSStore modifiesSStore;
  NextStore nextStore;
  StmtStore stmtStore;
  UsesSStore usesSStore;

  stmtStore.addStmt(1, StmtType::READ);
  stmtStore.addStmt(2, StmtType::READ);
  stmtStore.addStmt(3, StmtType::ASSIGN);
  stmtStore.addStmt(4, StmtType::ASSIGN);
  stmtStore.addStmt(5, StmtType::CALL);
  stmtStore.addStmt(6, StmtType::WHILE);
  stmtStore.addStmt(7, StmtType::ASSIGN);
  stmtStore.addStmt(8, StmtType::CALL);
  stmtStore.addStmt(9, StmtType::ASSIGN);
  stmtStore.addStmt(10, StmtType::IF);
  stmtStore.addStmt(11, StmtType::ASSIGN);
  stmtStore.addStmt(12, StmtType::ASSIGN);
  stmtStore.addStmt(13, StmtType::ASSIGN);
  stmtStore.addStmt(14, StmtType::IF);
  stmtStore.addStmt(15, StmtType::ASSIGN);
  stmtStore.addStmt(16, StmtType::ASSIGN);
  stmtStore.addStmt(17, StmtType::ASSIGN);
  stmtStore.addStmt(18, StmtType::ASSIGN);
  stmtStore.addStmt(19, StmtType::ASSIGN);
  stmtStore.addStmt(20, StmtType::CALL);
  stmtStore.addStmt(21, StmtType::ASSIGN);
  stmtStore.addStmt(22, StmtType::ASSIGN);
  stmtStore.addStmt(23, StmtType::PRINT);
  stmtStore.addStmt(24, StmtType::PRINT);
  stmtStore.addStmt(25, StmtType::PRINT);
  stmtStore.addStmt(26, StmtType::PRINT);

  modifiesSStore.addRelation(3, "x");
  modifiesSStore.addRelation(7, "x");
  modifiesSStore.addRelation(11, "x");
  modifiesSStore.addRelation(19, "x");

  modifiesSStore.addRelation(12, "y");
  modifiesSStore.addRelation(18, "y");

  modifiesSStore.addRelation(13, "z");
  modifiesSStore.addRelation(15, "z");
  modifiesSStore.addRelation(16, "z");
  modifiesSStore.addRelation(17, "z");

  modifiesSStore.addRelation(4, "i");
  modifiesSStore.addRelation(9, "i");

  modifiesSStore.addRelation(5, "x");
  modifiesSStore.addRelation(5, "b");
  modifiesSStore.addRelation(8, "z");
  modifiesSStore.addRelation(8, "v");
  modifiesSStore.addRelation(21, "z");
  modifiesSStore.addRelation(22, "v");

  usesSStore.addRelation(7, "x");
  usesSStore.addRelation(11, "x");
  usesSStore.addRelation(13, "x");
  usesSStore.addRelation(17, "x");
  usesSStore.addRelation(19, "x");

  usesSStore.addRelation(7, "y");
  usesSStore.addRelation(12, "y");
  usesSStore.addRelation(13, "y");
  usesSStore.addRelation(19, "y");

  usesSStore.addRelation(16, "z");
  usesSStore.addRelation(17, "z");
  usesSStore.addRelation(18, "z");
  usesSStore.addRelation(19, "z");

  usesSStore.addRelation(9, "i");
  usesSStore.addRelation(17, "i");

  usesSStore.addRelation(21, "v");
  usesSStore.addRelation(22, "z");

  nextStore.addRelation(1, 2);
  nextStore.addRelation(3, 4);
  nextStore.addRelation(4, 5);
  nextStore.addRelation(5, 6);
  nextStore.addRelation(6, 7);
  nextStore.addRelation(6, 14);
  nextStore.addRelation(7, 8);
  nextStore.addRelation(8, 9);
  nextStore.addRelation(9, 10);
  nextStore.addRelation(10, 11);
  nextStore.addRelation(10, 13);
  nextStore.addRelation(11, 12);
  nextStore.addRelation(12, 6);
  nextStore.addRelation(12, 14);
  nextStore.addRelation(13, 6);
  nextStore.addRelation(13, 14);
  nextStore.addRelation(14, 15);
  nextStore.addRelation(14, 16);
  nextStore.addRelation(15, 17);
  nextStore.addRelation(16, 17);
  nextStore.addRelation(17, 18);
  nextStore.addRelation(18, 19);
  nextStore.addRelation(19, 20);
  nextStore.addRelation(21, 22);

  SECTION("AffectsPairs") {
    AffectsReader affectsReader(affectsCache, modifiesSStore, nextStore,
                                stmtStore, usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    std::vector<std::pair<std::string, std::string>> expectedResults = {
        {"4", "9"},   {"4", "17"},  {"7", "7"},   {"7", "11"},  {"7", "13"},
        {"7", "17"},  {"7", "19"},  {"9", "9"},   {"9", "17"},  {"11", "7"},
        {"11", "17"}, {"11", "19"}, {"12", "7"},  {"12", "12"}, {"12", "13"},
        {"13", "16"}, {"15", "17"}, {"16", "17"}, {"17", "18"}, {"17", "19"},
        {"18", "19"}, {"21", "22"}};
    REQUIRE(compareVectorContents(result, expectedResults));
    REQUIRE(compareVectorContents(affectsReader.getAffects(4, StmtType::ASSIGN),
                                  std::vector<std::string> {"9", "17"}));
    REQUIRE(
        compareVectorContents(affectsReader.getAffectedBy(7, StmtType::ASSIGN),
                              std::vector<std::string> {"7", "11", "12"}));
    REQUIRE(compareVectorContents(
        affectsReader.getAffectedBy(19, StmtType::ASSIGN),
        std::vector<std::string> {"7", "11", "17", "18"}));
    REQUIRE(affectsReader.isAffects(7, 7));
    REQUIRE_FALSE(affectsReader.isAffects(7, 9));
    REQUIRE(affectsReader.isAffects(4, 9));
    REQUIRE(affectsReader.isAffects(4, 17));
    REQUIRE(affectsReader.isAffects(7, 7));
    REQUIRE(affectsReader.isAffects(7, 11));
    REQUIRE(affectsReader.isAffects(7, 13));
    REQUIRE(affectsReader.isAffects(7, 17));
    REQUIRE(affectsReader.isAffects(7, 19));
    REQUIRE(affectsReader.isAffects(9, 9));
    REQUIRE(affectsReader.isAffects(9, 17));
    REQUIRE(affectsReader.isAffects(11, 17));

    REQUIRE_FALSE(affectsReader.isAffects(1, 2));
    REQUIRE_FALSE(affectsReader.isAffects(3, 5));
    REQUIRE_FALSE(affectsReader.isAffects(6, 8));
    REQUIRE_FALSE(affectsReader.isAffects(10, 14));
    REQUIRE_FALSE(affectsReader.isAffects(12, 19));
    REQUIRE_FALSE(affectsReader.isAffects(14, 15));
    REQUIRE_FALSE(affectsReader.isAffects(20, 21));
    REQUIRE_FALSE(affectsReader.isAffects(23, 24));
    REQUIRE_FALSE(affectsReader.isAffects(25, 26));
    REQUIRE_FALSE(affectsReader.isAffects(27, 28));
    REQUIRE_FALSE(affectsReader.isAffects(29, 30));
  }
}
