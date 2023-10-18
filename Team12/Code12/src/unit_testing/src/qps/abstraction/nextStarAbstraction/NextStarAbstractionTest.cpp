#include <catch.hpp>

#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../mocks/MockPKBReader.h"
#include "../AbstractionTestUtils.h"
#include "NextStarAbstractionTestData.h"
#include "qps/abstraction/nextStarAbstraction/NextStarAbstraction.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"

TEST_CASE("NextStarAbstraction - Next*(Synonym, Synonym)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_NEXT_STAR_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetPrevTStmts = MOCK_NEXT_STAR_FIRST_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_NEXT_STAR_FIRST_STMTS_2D);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Integer)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetPrevTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_NEXT_STAR_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetNextTStmts = MOCK_NEXT_STAR_SECOND_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.getData() == MOCK_NEXT_STAR_SECOND_STMTS_2D);
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Synonym)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetNextTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetNextTStmts = MOCK_NEXT_STAR_SECOND_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Wildcard)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetNextTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Integer)_true") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockIsNextT = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Integer)_false") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockIsNextT = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_NEXT_STAR_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetPrevTStmts = MOCK_NEXT_STAR_FIRST_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Integer)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetPrevTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Wildcard)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
