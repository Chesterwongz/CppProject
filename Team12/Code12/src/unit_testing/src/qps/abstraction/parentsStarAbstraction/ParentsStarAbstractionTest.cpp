#include <catch.hpp>

#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../mocks/MockPKBReader.h"
#include "../AbstractionTestUtils.h"
#include "ParentsStarAbstractionTestData.h"
#include "qps/abstraction/parentsStarAbstraction/ParentsStarAbstraction.h"

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Synonym)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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

  REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_STARS_VECTOR);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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

  REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_STARS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE(
    "ParentsStarAbstraction - Parents*(Synonym, Integer)_no_immediate_parent") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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

  REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_STARS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Synonym)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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

  REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_STARS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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

  REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_STARS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE, MOCK_STORE);
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
