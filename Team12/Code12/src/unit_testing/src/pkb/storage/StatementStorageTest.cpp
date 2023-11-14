#include <unordered_set>
#include <catch.hpp>

#include "pkb/storage/entity_storage/StmtStore.h"

TEST_CASE("StmtStorage Tests") {
  StmtStore storage;

  storage.addStmt(1, StmtType::IF);
  storage.addStmt(2, StmtType::IF);
  storage.addStmt(3, StmtType::WHILE);
  storage.addStmt(4, StmtType::ASSIGN);
  storage.addStmt(5, StmtType::READ);
  storage.addStmt(6, StmtType::PRINT);

  SECTION("setStatement and getStatementNumbersFromStatementType") {
    REQUIRE(storage.getAllStmtsOf(StmtType::IF) ==
            std::unordered_set<int> {1, 2});
    REQUIRE(storage.getAllStmtsOf(StmtType::WHILE) ==
            std::unordered_set<int> {3});
    REQUIRE(storage.getAllStmtsOf(StmtType::ASSIGN) ==
            std::unordered_set<int> {4});
    REQUIRE(!storage.hasStmtType(StmtType::CALL));
  }

  SECTION("getAllStmtUsingVar") {
    REQUIRE(storage.getAllStmtsOf(StmtType::STMT) ==
            std::unordered_set<int> {1, 2, 3, 4, 5, 6});
  }

  SECTION("hasStmt") {
    REQUIRE(storage.hasStmt(1, StmtType::IF) == true);
    REQUIRE(storage.hasStmt(2, StmtType::IF) == true);
    REQUIRE(storage.hasStmt(3, StmtType::IF) == false);
    REQUIRE(storage.hasStmt(4, StmtType::ASSIGN) == true);
    REQUIRE(storage.hasStmt(5, StmtType::READ) == true);
    REQUIRE(storage.hasStmt(6, StmtType::PRINT) == true);
    REQUIRE(storage.hasStmt(7, StmtType::CALL) == false);
  }
}
