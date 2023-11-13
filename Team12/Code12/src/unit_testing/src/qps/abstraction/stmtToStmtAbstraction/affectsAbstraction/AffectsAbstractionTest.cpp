#include <catch.hpp>

#include "../../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../../mocks/mockReaders/MockAffectsReader.h"
#include "../../AbstractionTestUtils.h"
#include "AffectsAbstractionTestData.h"
#include "qps/abstraction/stmtToStmtAbstraction/affectsAbstraction/AffectsAbstraction.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"

TEST_CASE("AffectsAbstraction - Affects(Synonym, Synonym)_EMPTY") {
  MockAffectsReader mockReader = MockAffectsReader();
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, ASSIGN_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Synonym, Synonym)_assign_entity") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectsPairs = MOCK_AFFECTS_PAIRS;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, ASSIGN_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_AFFECTS_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Synonym, Synonym)_stmt_entity") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectsPairs = MOCK_AFFECTS_PAIRS;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_AFFECTS_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE(
    "AffectsAbstraction - Affects(Synonym, "
    "Synonym)_first_arg_not_assign_not_stmt") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectsPairs = MOCK_AFFECTS_PAIRS;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, CALL_ENTITY);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, ASSIGN_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE(
    "AffectsAbstraction - Affects(Synonym, "
    "Synonym)_second_arg_not_assign_not_stmt") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectsPairs = MOCK_AFFECTS_PAIRS;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, CALL_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE(
    "AffectsAbstraction - Affects(Synonym, "
    "Synonym)_both_not_assign_stmt") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectsPairs = MOCK_AFFECTS_PAIRS;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PRINT_ENTITY);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, READ_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Synonym, Integer)") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectedBy = MOCK_AFFECTED_BY;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, ASSIGN_ENTITY);
  unique_ptr<Integer> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.getDataAsStrings() == MOCK_AFFECTED_BY_COL);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Synonym, Integer)_not_affected") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectedBy = {};
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, ASSIGN_ENTITY);
  unique_ptr<Integer> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Synonym, Integer)_not_assign") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectedBy = MOCK_AFFECTED_BY;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, CALL_ENTITY);
  unique_ptr<Integer> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Synonym, Wildcard)") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectsPairs = MOCK_AFFECTS_PAIRS;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, ASSIGN_ENTITY);
  unique_ptr<Wildcard> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_AFFECTS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Integer, Synonym)") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffects = MOCK_AFFECTS;
  unique_ptr<Integer> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, ASSIGN_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.getDataAsStrings() == MOCK_AFFECTS_COL);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Integer, Synonym)_no_affected") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffects = {};
  unique_ptr<Integer> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, ASSIGN_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Integer, Wildcard)") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffects = MOCK_AFFECTS;
  unique_ptr<Integer> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<Wildcard> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}


TEST_CASE("AffectsAbstraction - Affects(Integer, Wildcard)_no_affected") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffects = {};
  unique_ptr<Integer> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, ASSIGN_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Integer, Integer)_true") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockIsAffects = true;
  unique_ptr<Integer> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Integer, Integer)_false") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockIsAffects = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Wildcard, Synonym)") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectsPairs = MOCK_AFFECTS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, ASSIGN_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_AFFECTS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Wildcard, Integer)") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectedBy = MOCK_AFFECTED_BY;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Wildcard, Integer) not followed") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectedBy = {};
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Wildcard, Wildcard)") {
  MockAffectsReader mockReader = MockAffectsReader();
  mockReader.mockAffectsPairs = MOCK_AFFECTS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("AffectsAbstraction - Affects(Wildcard, Wildcard)_EMPTY") {
  MockAffectsReader mockReader = MockAffectsReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, AFFECTS_ENUM, *mockArgument1, *mockArgument2);

  AffectsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
