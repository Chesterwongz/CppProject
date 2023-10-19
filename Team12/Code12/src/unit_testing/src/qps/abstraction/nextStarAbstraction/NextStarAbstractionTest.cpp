#include <catch.hpp>

#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../mocks/MockPKBReader.h"
#include "../AbstractionTestUtils.h"
#include "NextStarAbstractionTestData.h"
#include "qps/abstraction/nextStarAbstraction/NextStarAbstraction.h"

TEST_CASE("NextStarAbstraction - Next*(Synonym, Synonym)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_NEXT_STAR_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetPrevTStmts = MOCK_NEXT_STAR_FIRST_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_NEXT_STAR_FIRST_STMTS_2D);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Integer)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetPrevTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_NEXT_STAR_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextTStmts = MOCK_NEXT_STAR_SECOND_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.getDataAsStrings() == MOCK_NEXT_STAR_SECOND_STMTS_2D);
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Synonym)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextTStmts = MOCK_NEXT_STAR_SECOND_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Wildcard)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Integer)_true") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockIsNextT = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Integer)_false") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockIsNextT = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_NEXT_STAR_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetPrevTStmts = MOCK_NEXT_STAR_FIRST_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Integer)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetPrevTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Wildcard)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
