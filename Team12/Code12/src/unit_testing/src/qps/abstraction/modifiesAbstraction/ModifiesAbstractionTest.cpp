#include <catch.hpp>

#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../mocks/MockPKBReader.h"
#include "../AbstractionTestUtils.h"
#include "ModifiesAbstractionTestData.h"
#include "qps/abstraction/modifiesAbstraction/ModifiesAbstraction.h"

TEST_CASE("ModifiesAbstraction - Modifies(Synonym, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ModifiesAbstraction - Modifies(Synonym, Synonym_empty)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("ModifiesAbstraction - Modifies(Synonym, Ident)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockStatementsModifying = MOCK_MODIFYING_STATEMENTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings().size() == 3);
  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFYING_STATEMENTS_COL);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("ModifiesAbstraction - Modifies(Synonym, Ident)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Synonym, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTORS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("ModifiesAbstraction - Modifies(Synonym, Wildcard)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockVariablesModifiedBy = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTORS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Synonym)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Ident)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockIsVariableModifiedBy = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Ident)_not_modified") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  mockReader.mockIsVariableModifiedBy = false;
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockVariablesModifiedBy = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Wildcard)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTORS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Synonym)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Ident)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockStatementsModifying = MOCK_MODIFYING_STATEMENTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Ident)_empty") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Wildcard)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
