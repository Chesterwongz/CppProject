#include <catch.hpp>

#include "../../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../../mocks/mockReaders/MockModifiesReader.h"
#include "../../AbstractionTestUtils.h"
#include "ModifiesAbstractionTestData.h"
#include "qps/abstraction/stmtOrProcToVarAbstraction/modifiesAbstraction/ModifiesAbstraction.h"

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Synonym)") {
  MockModifiesReader mockReader = MockModifiesReader();
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

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Synonym)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
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

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Ident)") {
  MockModifiesReader mockReader = MockModifiesReader();
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
  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFYING_COL);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Ident)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
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

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Wildcard)") {
  MockModifiesReader mockReader = MockModifiesReader();
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

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Wildcard)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
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

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Synonym)") {
  MockModifiesReader mockReader = MockModifiesReader();
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

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Synonym)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, MODIFIES_ENUM,
                                      *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Ident)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockProceduresModifying = MOCK_MODIFYING_PROCEDURES;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, MODIFIES_ENUM,
                                      *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings().size() == 3);
  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFYING_COL);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Ident)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, MODIFIES_ENUM,
                                      *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Wildcard)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockModifiesProcPairs = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, MODIFIES_ENUM,
                                      *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTORS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Wildcard)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, MODIFIES_ENUM,
                                      *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Synonym)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockVariablesModifiedBy = MOCK_MODIFYING_VARIABLES;
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
  MockModifiesReader mockReader = MockModifiesReader();
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
  MockModifiesReader mockReader = MockModifiesReader();
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
  MockModifiesReader mockReader = MockModifiesReader();
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
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockVariablesModifiedBy = MOCK_MODIFYING_VARIABLES;
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
  MockModifiesReader mockReader = MockModifiesReader();
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

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Synonym)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockVarsModifiedByProc = MOCK_MODIFIED_FOR_PROCS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, MODIFIES_ENUM,
                                      *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTOR_FOR_PROCS);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Synonym)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, MODIFIES_ENUM,
                                      *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Ident)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockIsVariableModifiedByProc = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, MODIFIES_ENUM,
                                      *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Ident)_not_modified") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  mockReader.mockIsVariableModifiedBy = false;
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, MODIFIES_ENUM,
                                      *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Wildcard)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockVarsModifiedByProc = MOCK_MODIFIED_FOR_PROCS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, MODIFIES_ENUM,
                                      *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Wildcard)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, MODIFIES_ENUM,
                                      *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Synonym)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Synonym)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Ident)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockStatementsModifying = MOCK_MODIFYING_STATEMENTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Ident)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Wildcard)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Wildcard)_EMPTY") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}
