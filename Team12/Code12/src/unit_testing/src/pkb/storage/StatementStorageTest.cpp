#include <catch.hpp>

#include "pkb/storage/entitystorage/StmtStorage.h"

TEST_CASE("StmtStorage Tests") {
  StmtStorage storage;

  storage.setStatement(1, StmtType::IF);
  storage.setStatement(2, StmtType::IF);
  storage.setStatement(3, StmtType::WHILE);
  storage.setStatement(4, StmtType::ASSIGN);
  storage.setStatement(5, StmtType::READ);
  storage.setStatement(6, StmtType::PRINT);

  SECTION("setStatement and getStatementNumbersFromStatementType") {
    REQUIRE(storage.getStatementNumbersFromStatementType(StmtType::IF) ==
            std::set<int>{1, 2});
    REQUIRE(storage.getStatementNumbersFromStatementType(StmtType::WHILE) ==
            std::set<int>{3});
    REQUIRE(storage.getStatementNumbersFromStatementType(StmtType::ASSIGN) ==
            std::set<int>{4});
    REQUIRE(storage.getStatementNumbersFromStatementType(StmtType::CALL) ==
            std::set<int>{});
  }

  SECTION("getAllStatements") {
    REQUIRE(storage.getAllStatements() == std::set<int>{1, 2, 3, 4, 5, 6});
  }

  SECTION("getStatementTypeFromStatementNumber") {
    REQUIRE(storage.getStatementTypeFromStatementNumber(1) == StmtType::IF);
    REQUIRE(storage.getStatementTypeFromStatementNumber(2) == StmtType::IF);
    REQUIRE(storage.getStatementTypeFromStatementNumber(3) == StmtType::WHILE);
    REQUIRE(storage.getStatementTypeFromStatementNumber(4) == StmtType::ASSIGN);
    REQUIRE(storage.getStatementTypeFromStatementNumber(5) == StmtType::READ);
    REQUIRE(storage.getStatementTypeFromStatementNumber(6) == StmtType::PRINT);
    REQUIRE(storage.getStatementTypeFromStatementNumber(7) ==
            StmtType::INVALID);
  }

  SECTION("isStatementType") {
    REQUIRE(storage.isStatementType(1, StmtType::IF) == true);
    REQUIRE(storage.isStatementType(2, StmtType::IF) == true);
    REQUIRE(storage.isStatementType(3, StmtType::IF) == false);
    REQUIRE(storage.isStatementType(4, StmtType::ASSIGN) == true);
    REQUIRE(storage.isStatementType(5, StmtType::READ) == true);
    REQUIRE(storage.isStatementType(6, StmtType::PRINT) == true);
    REQUIRE(storage.isStatementType(7, StmtType::INVALID) == true);
    REQUIRE(storage.isStatementType(7, StmtType::CALL) == false);
  }
}
