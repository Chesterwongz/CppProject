#pragma once

#include <catch.hpp>

#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../mocks/MockPKBReader.h"
#include "../AbstractionTestUtils.h"
#include "UsesAbstractionTestData.h"
#include "qps/abstraction/usesAbstraction/UsesAbstraction.h"

TEST_CASE("UsesAbstraction - Uses(Synonym, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  mockReader.mockAllUsedVariables = MOCK_USED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_USED_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("UsesAbstraction - Uses(Synonym, Synonym)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("UsesAbstraction - Uses(Synonym, Ident)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  mockReader.mockStatementsUsing = MOCK_USING_STATEMENTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_USING_STATEMENTS_COL);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("UsesAbstraction - Uses(Synonym, Ident)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("UsesAbstraction - Uses(Synonym, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  mockReader.mockAllUsedVariables = MOCK_USED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_USED_VECTORS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("UsesAbstraction - Uses(Synonym, Wildcard)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("UsesAbstraction - Uses(Integer, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  mockReader.mockVariablesUsedBy = MOCK_USED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_USED_VECTORS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("UsesAbstraction - Uses(Integer, Synonym)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("UsesAbstraction - Uses(Integer, Ident)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  mockReader.mockIsVariableUsedBy = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("UsesAbstraction - Uses(Integer, Ident)_false") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  mockReader.mockIsVariableUsedBy = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("UsesAbstraction - Uses(Integer, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  mockReader.mockVariablesUsedBy = MOCK_USED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("UsesAbstraction - Uses(Integer, Wildcard)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("UsesAbstraction - Uses(Wildcard, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  mockReader.mockAllUsedVariables = MOCK_USED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

TEST_CASE("UsesAbstraction - Uses(Wildcard, Synonym)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

TEST_CASE("UsesAbstraction - Uses(Wildcard, Ident)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  mockReader.mockStatementsUsing = MOCK_USING_STATEMENTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

TEST_CASE("UsesAbstraction - Uses(Wildcard, Ident)_false") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

TEST_CASE("UsesAbstraction - Uses(Wildcard, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  mockReader.mockAllUsedVariables = MOCK_USED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

TEST_CASE("UsesAbstraction - Uses(Wildcard, Wildcard)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}
