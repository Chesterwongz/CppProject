#include <catch.hpp>

#include "../../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../../mocks/mockReaders/MockModifiesReader.h"
#include "../../AbstractionTestUtils.h"
#include "ModifiesAbstractionTestData.h"
#include "qps/abstraction/stmtOrProcToVarAbstraction/modifiesAbstraction/ModifiesAbstraction.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Synonym)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, ASSIGN_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, VARIABLE_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Synonym)_PRINT") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PRINT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Synonym)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Ident)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockStatementsModifying = MOCK_MODIFYING_STATEMENTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings().size() == 3);
  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFYING_COL);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Ident)_PRINT") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockStatementsModifying = MOCK_MODIFYING_STATEMENTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PRINT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Ident)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Wildcard)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTORS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Wildcard)_PRINT") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PRINT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(StmtSynonym, Wildcard)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Synonym)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockModifiesProcPairs = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, VARIABLE_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Synonym)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, VARIABLE_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Ident)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockProceduresModifying = MOCK_MODIFYING_PROCEDURES;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings().size() == 3);
  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFYING_COL);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Ident)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Wildcard)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockModifiesProcPairs = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTORS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcSynonym, Wildcard)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Synonym)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockVariablesModifiedBy = MOCK_MODIFYING_VARIABLES;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, VARIABLE_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTORS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Synonym)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Ident)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockIsVariableModifiedBy = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Ident)_not_modified") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  mockReader.mockIsVariableModifiedBy = false;
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Wildcard)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockVariablesModifiedBy = MOCK_MODIFYING_VARIABLES;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Integer, Wildcard)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Synonym)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockVarsModifiedByProc = MOCK_MODIFIED_FOR_PROCS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, VARIABLE_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_MODIFIED_VECTOR_FOR_PROCS);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Synonym)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Ident)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockIsVariableModifiedByProc = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Ident)_not_modified") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  mockReader.mockIsVariableModifiedBy = false;
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Wildcard)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockIsVariableModifiedByProc = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(ProcName, Wildcard)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Synonym)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Synonym)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Ident)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockStatementsModifying = MOCK_MODIFYING_STATEMENTS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Ident)_empty") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Wildcard)") {
  MockModifiesReader mockReader = MockModifiesReader();
  mockReader.mockAllModifiedVariables = MOCK_MODIFIED_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ModifiesAbstraction - Modifies(Wildcard, Wildcard)_EMPTY") {
  MockModifiesReader mockReader = MockModifiesReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, MODIFIES_ENUM, *mockArgument1, *mockArgument2);

  ModifiesAbstraction abstraction(*abstractionParams);
  REQUIRE_THROWS_WITH(abstraction.evaluate(),
                      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}
