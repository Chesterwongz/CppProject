#include <catch.hpp>

#include "../../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../../mocks/mockReaders/MockFollowsReader.h"
#include "../../AbstractionTestUtils.h"
#include "FollowsAbstractionTestData.h"
#include "qps/abstraction/stmtToStmtAbstraction/followsAbstraction/FollowsAbstraction.h"

TEST_CASE("FollowsAbstraction - Follows(Synonym, Synonym)_EMPTY") {
  MockFollowsReader mockReader = MockFollowsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("FollowsAbstraction - Follows(Synonym, Synonym)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_FOLLOWS_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsAbstraction - Follows(Synonym, Integer)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowed = MOCK_FOLLOWED;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings().size() == 1);
  REQUIRE(resultTable.getDataAsStrings().at(0).size() == 1);
  REQUIRE(resultTable.getDataAsStrings().at(0).at(0) == MOCK_FOLLOWED[0]);
}

TEST_CASE("FollowsAbstraction - Follows(Synonym, Integer) not followed") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowed = MOCK_NO_FOLLOWED;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Synonym, Wildcard)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_FOLLOWS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Synonym)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowing = MOCK_FOLLOWED;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.getDataAsStrings().size() == 1);
  REQUIRE(resultTable.getDataAsStrings().at(0).size() == 1);
  REQUIRE(resultTable.getDataAsStrings().at(0).at(0) == MOCK_FOLLOWED[0]);
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Synonym)_no followed") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowing = MOCK_NO_FOLLOWED;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Wildcard)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowing = MOCK_FOLLOWED;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Wildcard)_no followed") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowing = MOCK_NO_FOLLOWED;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Integer)_true") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockIsFollows = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Integer)_false") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockIsFollows = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Synonym)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_FOLLOWS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Integer)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowed = MOCK_FOLLOWED;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Integer) not followed") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowed = MOCK_NO_FOLLOWED;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Wildcard)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Wildcard)_EMPTY") {
  MockFollowsReader mockReader = MockFollowsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  unique_ptr<AbstractArgument> mockArgument2 =
      ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
  Context mockContext = Context();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, mockContext, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
