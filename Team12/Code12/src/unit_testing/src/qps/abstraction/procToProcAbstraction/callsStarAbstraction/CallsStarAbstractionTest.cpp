#include <catch.hpp>

#include "../../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../../mocks/mockReaders/MockCallsReader.h"
#include "../../AbstractionTestUtils.h"
#include "CallsStarAbstractionTestData.h"
#include "qps/abstraction/procToProcAbstraction/callsStarAbstraction/CallsStarAbstraction.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/wildcard/Wildcard.h"

TEST_CASE("CallsStarAbstraction - CallsStar(ProcSynonym, ProcSynonym)") {
  MockCallsReader mockReader = MockCallsReader();
  mockReader.mockCallsStarPairs = MOCK_CALLS_STAR_DATA::MOCK_CALL_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, PROCEDURE_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() ==
          MOCK_CALLS_STAR_DATA::MOCK_CALL_STAR_PAIRS_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(ProcSynonym, ProcSynonym)_empty") {
  MockCallsReader mockReader = MockCallsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, PROCEDURE_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(ProcSynonym, ProcName)") {
  MockCallsReader mockReader = MockCallsReader();
  mockReader.mockCallerProcsStar = MOCK_CALLS_STAR_DATA::MOCK_CALLER_STAR_PROCS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() ==
          MOCK_CALLS_STAR_DATA::MOCK_CALLER_STAR_PROCS_COL);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(ProcSynonym, ProcName)_empty") {
  MockCallsReader mockReader = MockCallsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(ProcSynonym, Wildcard)") {
  MockCallsReader mockReader = MockCallsReader();
  mockReader.mockCallsStarPairs = MOCK_CALLS_STAR_DATA::MOCK_CALL_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() ==
          MOCK_CALLS_STAR_DATA::MOCK_CALLED_STAR_VECTORS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(ProcSynonym, Wildcard)_empty") {
  MockCallsReader mockReader = MockCallsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(ProcName, ProcSynonym)") {
  MockCallsReader mockReader = MockCallsReader();
  mockReader.mockCalleeProcsStar = MOCK_CALLS_STAR_DATA::MOCK_CALLEE_STAR_PROCS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, PROCEDURE_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() ==
          MOCK_CALLS_STAR_DATA::MOCK_CALLEE_STAR_PROCS_COL);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(ProcName, ProcSynonym)_empty") {
  MockCallsReader mockReader = MockCallsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, PROCEDURE_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(ProcName, ProcName)") {
  MockCallsReader mockReader = MockCallsReader();
  mockReader.mockHasCallsT = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(ProcName, ProcName)_false") {
  MockCallsReader mockReader = MockCallsReader();
  mockReader.mockHasCallsT = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(ProcName, Wildcard)") {
  MockCallsReader mockReader = MockCallsReader();
  mockReader.mockHasCallsT = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(ProcName, Wildcard)_empty") {
  MockCallsReader mockReader = MockCallsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(Wildcard, ProcSynonym)") {
  MockCallsReader mockReader = MockCallsReader();
  mockReader.mockCallsStarPairs = MOCK_CALLS_STAR_DATA::MOCK_CALL_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, PROCEDURE_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() ==
          MOCK_CALLS_STAR_DATA::MOCK_CALLED_STAR_VECTORS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(Wildcard, ProcSynonym)_empty") {
  MockCallsReader mockReader = MockCallsReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, PROCEDURE_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(Wildcard, ProcName)") {
  MockCallsReader mockReader = MockCallsReader();
  mockReader.mockHasCallsT = true;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(Wildcard, ProcName)_false") {
  MockCallsReader mockReader = MockCallsReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(Wildcard, Wildcard)") {
  MockCallsReader mockReader = MockCallsReader();
  mockReader.mockCallsStarPairs = MOCK_CALLS_STAR_DATA::MOCK_CALL_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("CallsStarAbstraction - CallsStar(Wildcard, Wildcard)_empty") {
  MockCallsReader mockReader = MockCallsReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, CALLS_ENUM, *mockArgument1, *mockArgument2);

  CallsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
