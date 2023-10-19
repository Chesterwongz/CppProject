#include <unordered_set>
#include <catch.hpp>

#include "../../common/utils/HelperFunctions.h"
#include "pkb/facade/PKBReader.h"
#include "pkb/facade/PKBWriter.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/AffectsReader.h"

TEST_CASE("AffectsReader Tests 1") {
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
  nextStore.addRelation(6, 7);
  nextStore.addRelation(7, 8);
  nextStore.addRelation(7, 9);
  nextStore.addRelation(8, 10);
  nextStore.addRelation(9, 10);
  nextStore.addRelation(10, 11);
  nextStore.addRelation(11, 12);

  SECTION("AffectsPairs") {
    AffectsReader affectsReader(modifiesSStore, nextStore, stmtStore,
                                usesSStore);
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
        compareVectorContents(affectsReader.getAffects(1),
                              std::vector<std::string> {"4", "8", "10", "12"}));
    REQUIRE(
        compareVectorContents(affectsReader.getAffects(4),
                              std::vector<std::string> {"4", "8", "10", "12"}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(9),
                                  std::vector<std::string> {"10"}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(12),
                                  std::vector<std::string> {}));
    REQUIRE(compareVectorContents(
        affectsReader.getAffectedBy(12),
        std::vector<std::string> {"1", "4", "8", "10", "11"}));
    REQUIRE(compareVectorContents(affectsReader.getAffectedBy(6),
                                  std::vector<std::string> {"2", "6"}));
    REQUIRE(compareVectorContents(affectsReader.getAffectedBy(1),
                                  std::vector<std::string> {}));
    REQUIRE(affectsReader.isAffects(1, 4));
    REQUIRE(affectsReader.isAffects(6, 10));
    REQUIRE_FALSE(affectsReader.isAffects(6, 11));
  }
}

TEST_CASE("AffectsReader Tests 2 - Code 7") {
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
    AffectsReader affectsReader(modifiesSStore, nextStore, stmtStore,
                                usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(compareVectorContents(
        result, std::vector<std::pair<std::string, std::string>> {{"1", "5"},
                                                                  {"3", "5"}}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(1),
                                  std::vector<std::string> {"5"}));
    REQUIRE(compareVectorContents(affectsReader.getAffectedBy(5),
                                  std::vector<std::string> {"1", "3"}));
    REQUIRE(affectsReader.isAffects(1, 5));
    REQUIRE(affectsReader.isAffects(3, 5));
    REQUIRE_FALSE(affectsReader.isAffects(2, 4));
  }
}

TEST_CASE("AffectsReader Tests 3 - Code 8") {
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
    AffectsReader affectsReader(modifiesSStore, nextStore, stmtStore,
                                usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(compareVectorContents(
        result, std::vector<std::pair<std::string, std::string>> {{"1", "3"}}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(1),
                                  std::vector<std::string> {"3"}));
    REQUIRE(compareVectorContents(affectsReader.getAffectedBy(3),
                                  std::vector<std::string> {"1"}));
    REQUIRE(compareVectorContents(affectsReader.getAffectedBy(4),
                                  std::vector<std::string> {}));
    REQUIRE(affectsReader.isAffects(1, 3));
    REQUIRE_FALSE(affectsReader.isAffects(3, 4));
  }
}

TEST_CASE("AffectsReader Tests 4 - Code 9") {
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
    AffectsReader affectsReader(modifiesSStore, nextStore, stmtStore,
                                usesSStore);
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
    REQUIRE(compareVectorContents(affectsReader.getAffects(6),
                                  std::vector<std::string> {"9", "10"}));
    REQUIRE(compareVectorContents(affectsReader.getAffectedBy(11),
                                  std::vector<std::string> {"7", "9"}));
    REQUIRE(affectsReader.isAffects(2, 3));
    REQUIRE(affectsReader.isAffects(7, 11));
    REQUIRE_FALSE(affectsReader.isAffects(6, 11));
  }
}

TEST_CASE("AffectsReader Tests 5 - Code 10") {
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
    AffectsReader affectsReader(modifiesSStore, nextStore, stmtStore,
                                usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(compareVectorContents(
        result, std::vector<std::pair<std::string, std::string>> {}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(6),
                                  std::vector<std::string> {}));
    REQUIRE_FALSE(affectsReader.isAffects(1, 2));
  }
}

TEST_CASE("AffectsReader Tests 6 - Code 11") {
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
    AffectsReader affectsReader(modifiesSStore, nextStore, stmtStore,
                                usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(compareVectorContents(
        result, std::vector<std::pair<std::string, std::string>> {}));
    REQUIRE(compareVectorContents(affectsReader.getAffects(6),
                                  std::vector<std::string> {}));
    REQUIRE_FALSE(affectsReader.isAffects(2, 3));
  }
}
