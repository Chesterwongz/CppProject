#include <catch.hpp>

#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../mocks/MockPKBReader.h"
#include "../AbstractionTestUtils.h"
#include "NextAbstractionTestData.h"
#include "qps/abstraction/nextAbstraction/NextAbstraction.h"

TEST_CASE("NextAbstraction - Next(Synonym, Synonym)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("NextAbstraction - Next(Synonym, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextPairs = MOCK_NEXT_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_NEXT_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("NextAbstraction - Next(Synonym, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetPrevStmts = MOCK_NEXT_FIRST_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_NEXT_FIRST_STMTS_2D);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("NextAbstraction - Next(Synonym, Integer)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetPrevStmts = MOCK_NO_NEXT_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextAbstraction - Next(Synonym, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextPairs = MOCK_NEXT_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_NEXT_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("NextAbstraction - Next(Integer, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextStmts = MOCK_NEXT_SECOND_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.getData() == MOCK_NEXT_SECOND_STMTS_2D);
}

TEST_CASE("NextAbstraction - Next(Integer, Synonym)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextStmts = MOCK_NO_NEXT_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextAbstraction - Next(Integer, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextStmts = MOCK_NEXT_SECOND_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextAbstraction - Next(Integer, Wildcard)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextStmts = MOCK_NO_NEXT_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextAbstraction - Next(Integer, Integer)_true") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockIsNext = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextAbstraction - Next(Integer, Integer)_false") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockIsNext = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextAbstraction - Next(Wildcard, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextPairs = MOCK_NEXT_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_NEXT_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("NextAbstraction - Next(Wildcard, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetPrevStmts = MOCK_NEXT_FIRST_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextAbstraction - Next(Wildcard, Integer)_no_next") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetPrevStmts = MOCK_NO_NEXT_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("NextAbstraction - Next(Wildcard, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockGetNextPairs = MOCK_NEXT_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("NextAbstraction - Next(Wildcard, Wildcard)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, NEXT_ENUM, *mockArgument1, *mockArgument2);

  NextAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
