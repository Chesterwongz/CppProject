#include <catch.hpp>

#include "../../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../../mocks/mockReaders/MockParentsReader.h"
#include "../../AbstractionTestUtils.h"
#include "ParentsStarAbstractionTestData.h"
#include "qps/abstraction/stmtToStmtAbstraction/parentsStarAbstraction/ParentsStarAbstraction.h"

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Synonym)_EMPTY") {
  MockParentsReader mockReader = MockParentsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParams(mockReader, mockContext, PARENTS_STAR_ENUM,
                                  *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Synonym)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParams(mockReader, mockContext, PARENTS_STAR_ENUM,
                                  *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_PARENT_CHILD_STARS_VECTOR);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Integer)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentStarOf = MOCK_PARENT_STARS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_PARENT_CHILD_STARS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE(
    "ParentsStarAbstraction - Parents*(Synonym, Integer)_no_immediate_parent") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentStarOf = {};
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Wildcard)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParams(mockReader, mockContext, PARENTS_STAR_ENUM,
                                  *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_PARENT_CHILD_STARS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Synonym)_EMPTY") {
  MockParentsReader mockReader = MockParentsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParams(mockReader, mockContext, PARENTS_STAR_ENUM,
                                  *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Synonym)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockChildrenStar = MOCK_CHILD_STARS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParams(mockReader, mockContext, PARENTS_STAR_ENUM,
                                  *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_PARENT_CHILD_STARS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Integer)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockIsParentStar = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Integer)_false") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockIsParentStar = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Integer)_same_integer") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockIsParentStar = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Wildcard)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockChildrenStar = MOCK_CHILD_STARS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParams(mockReader, mockContext, PARENTS_STAR_ENUM,
                                  *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Wildcard)_empty") {
  MockParentsReader mockReader = MockParentsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParams(mockReader, mockContext, PARENTS_STAR_ENUM,
                                  *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Synonym)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParams(mockReader, mockContext, PARENTS_STAR_ENUM,
                                  *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_PARENT_CHILD_STARS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Integer)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentStarOf = MOCK_PARENT_STARS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE(
    "ParentsStarAbstraction - Parents*(Wildcard, "
    "Integer)_no_immediate_parent") {
  MockParentsReader mockReader = MockParentsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Wildcard)") {
  MockParentsReader mockReader = MockParentsReader();
  mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParams(mockReader, mockContext, PARENTS_STAR_ENUM,
                                  *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Wildcard)_EMPTY") {
  MockParentsReader mockReader = MockParentsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams =
      createMockAbstractionParams(mockReader, mockContext, PARENTS_STAR_ENUM,
                                  *mockArgument1, *mockArgument2);

  ParentsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
