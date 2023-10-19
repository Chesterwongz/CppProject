#include <catch.hpp>

#include "../../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../../mocks/mockReaders/MockUsesReader.h"
#include "../../AbstractionTestUtils.h"
#include "UsesAbstractionTestData.h"
#include "qps/abstraction/stmtOrProcToVarAbstraction/usesAbstraction/UsesAbstraction.h"

TEST_CASE("UsesAbstraction - Uses(StmtSynonym, Synonym)") {
  MockUsesReader mockReader = MockUsesReader();
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

  REQUIRE(resultTable.getDataAsStrings() == MOCK_USED_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("UsesAbstraction - Uses(StmtSynonym, Synonym)_empty") {
  MockUsesReader mockReader = MockUsesReader();
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

TEST_CASE("UsesAbstraction - Uses(StmtSynonym, Ident)") {
  MockUsesReader mockReader = MockUsesReader();
  mockReader.mockStatementsUsing = MOCK_USING_STATEMENTS_1;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_USING_STATEMENTS_COL);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("UsesAbstraction - Uses(StmtSynonym, Ident)_empty") {
  MockUsesReader mockReader = MockUsesReader();
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

TEST_CASE("UsesAbstraction - Uses(StmtSynonym, Wildcard)") {
  MockUsesReader mockReader = MockUsesReader();
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

  REQUIRE(resultTable.getDataAsStrings() == MOCK_USED_VECTORS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("UsesAbstraction - Uses(StmtSynonym, Wildcard)_empty") {
  MockUsesReader mockReader = MockUsesReader();
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

TEST_CASE("UsesAbstraction - Uses(ProcSynonym, Synonym)") {
  MockUsesReader mockReader = MockUsesReader();
  mockReader.mockUsesProcPairs = MOCK_USED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, USES_ENUM,
                                      *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_USED_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("UsesAbstraction - Uses(ProcSynonym, Synonym)_empty") {
  MockUsesReader mockReader = MockUsesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, USES_ENUM,
                                      *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("UsesAbstraction - Uses(ProcSynonym, Ident)") {
  MockUsesReader mockReader = MockUsesReader();
  mockReader.mockProcUsing = MOCK_USING_PROCEDURES;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, USES_ENUM,
                                      *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_USING_STATEMENTS_COL);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("UsesAbstraction - Uses(ProcSynonym, Ident)_empty") {
  MockUsesReader mockReader = MockUsesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, USES_ENUM,
                                      *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("UsesAbstraction - Uses(ProcSynonym, Wildcard)") {
  MockUsesReader mockReader = MockUsesReader();
  mockReader.mockUsesProcPairs = MOCK_USED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, USES_ENUM,
                                      *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_USED_VECTORS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("UsesAbstraction - Uses(ProcSynonym, Wildcard)_empty") {
  MockUsesReader mockReader = MockUsesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParamsProc(mockReader, mockContext, USES_ENUM,
                                      *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("UsesAbstraction - Uses(Integer, Synonym)") {
  MockUsesReader mockReader = MockUsesReader();
  mockReader.mockVariablesUsedBy = MOCK_USING_STATEMENTS_2;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_USED_VECTORS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("UsesAbstraction - Uses(Integer, Synonym)_empty") {
  MockUsesReader mockReader = MockUsesReader();
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
  MockUsesReader mockReader = MockUsesReader();
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
  MockUsesReader mockReader = MockUsesReader();
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
  MockUsesReader mockReader = MockUsesReader();
  mockReader.mockVariablesUsedBy = MOCK_USING_STATEMENTS_2;
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
  MockUsesReader mockReader = MockUsesReader();
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

TEST_CASE("UsesAbstraction - Uses(ProcName, Synonym)") {
  MockUsesReader mockReader = MockUsesReader();
  mockReader.mockVarUsedByProc = MOCK_USED_FOR_PROCS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_USED_VECTOR_FOR_PROCS);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("UsesAbstraction - Uses(ProcName, Synonym)_empty") {
  MockUsesReader mockReader = MockUsesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
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

TEST_CASE("UsesAbstraction - Uses(ProcName, Ident)") {
  MockUsesReader mockReader = MockUsesReader();
  mockReader.mockIsVariableUsedByProc = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("UsesAbstraction - Uses(ProcName, Ident)_false") {
  MockUsesReader mockReader = MockUsesReader();
  mockReader.mockIsVariableUsedByProc = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("UsesAbstraction - Uses(ProcName, Wildcard)") {
  MockUsesReader mockReader = MockUsesReader();
  mockReader.mockVarUsedByProc = MOCK_USED_FOR_PROCS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, USES_ENUM, *mockArgument1, *mockArgument2);

  UsesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("UsesAbstraction - Uses(ProcName, Wildcard)_empty") {
  MockUsesReader mockReader = MockUsesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
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
  MockUsesReader mockReader = MockUsesReader();
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
  MockUsesReader mockReader = MockUsesReader();
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
  MockUsesReader mockReader = MockUsesReader();
  mockReader.mockStatementsUsing = MOCK_USING_STATEMENTS_1;
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
  MockUsesReader mockReader = MockUsesReader();
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
  MockUsesReader mockReader = MockUsesReader();
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
  MockUsesReader mockReader = MockUsesReader();
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
