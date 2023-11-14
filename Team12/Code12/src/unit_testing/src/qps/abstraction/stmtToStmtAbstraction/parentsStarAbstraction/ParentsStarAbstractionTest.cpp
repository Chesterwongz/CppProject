#include <catch.hpp>

#include "../../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../../mocks/mockReaders/MockParentsReader.h"
#include "../../AbstractionTestUtils.h"
#include "ParentsStarAbstractionTestData.h"
#include "qps/abstraction/stmtToStmtAbstraction/parentsStarAbstraction/ParentsStarAbstraction.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Synonym)_EMPTY") {
  MockParentsReader mockReader = MockParentsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Synonym)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_PARENT_CHILD_STARS_VECTOR);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE(
    "ParentsStarAbstraction - Parents*(Synonym, Synonym)_not_if_or_while") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, READ_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Integer)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentStarOf = MOCK_PARENT_STARS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_PARENT_CHILD_STARS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE(
    "ParentsStarAbstraction - Parents*(Synonym, Integer)_not_if_or_while") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentStarOf = MOCK_PARENT_STARS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PRINT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE(
    "ParentsStarAbstraction - Parents*(Synonym, Integer)_no_immediate_parent") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentStarOf = {};
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Wildcard)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_PARENT_CHILD_STARS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE(
    "ParentsStarAbstraction - Parents*(Synonym, Wildcard)_not_if_or_while") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, READ_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Wildcard)_EMPTY") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentChildStarPairs = {};
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Synonym)_EMPTY") {
  MockParentsReader mockReader = MockParentsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Synonym)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockChildrenStar = MOCK_CHILD_STARS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_PARENT_CHILD_STARS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Integer)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockIsParentStar = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Integer)_false") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockIsParentStar = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Integer)_same_integer") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockIsParentStar = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Wildcard)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockIsParentStar = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Wildcard)_empty") {
  MockParentsReader mockReader = MockParentsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Synonym)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_PARENT_CHILD_STARS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Integer)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockIsParentStar = true;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE(
    "ParentsStarAbstraction - Parents*(Wildcard, "
    "Integer)_no_immediate_parent") {
  MockParentsReader mockReader = MockParentsReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Wildcard)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Wildcard)_EMPTY") {
  MockParentsReader mockReader = MockParentsReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, PARENTS_STAR_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
