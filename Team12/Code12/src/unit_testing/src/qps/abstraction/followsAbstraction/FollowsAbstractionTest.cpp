#include <catch.hpp>

#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../mocks/MockPKBReader.h"
#include "../AbstractionTestUtils.h"
#include "FollowsAbstractionTestData.h"
#include "qps/abstraction/followsAbstraction/FollowsAbstraction.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"

TEST_CASE("FollowsAbstraction - Follows(Synonym, Synonym)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("FollowsAbstraction - Follows(Synonym, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_FOLLOWS_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsAbstraction - Follows(Synonym, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowed = MOCK_FOLLOWED;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<Integer> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData().size() == 1);
  REQUIRE(resultTable.getData().at(0).size() == 1);
  REQUIRE(resultTable.getData().at(0).at(0) == MOCK_FOLLOWED);
}

TEST_CASE("FollowsAbstraction - Follows(Synonym, Integer) not followed") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowed = MOCK_NO_FOLLOWED;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<Integer> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Synonym, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<Wildcard> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_FOLLOWS_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowing = MOCK_FOLLOWED;
  unique_ptr<Integer> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.getData().size() == 1);
  REQUIRE(resultTable.getData().at(0).size() == 1);
  REQUIRE(resultTable.getData().at(0).at(0) == MOCK_FOLLOWED);
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Synonym)_no followed") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowing = MOCK_NO_FOLLOWED;
  unique_ptr<Integer> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowing = MOCK_FOLLOWED;
  unique_ptr<Integer> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<Wildcard> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Wildcard)_no followed") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowing = MOCK_NO_FOLLOWED;
  unique_ptr<Integer> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Integer)_true") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockIsFollows = true;
  unique_ptr<Integer> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Integer)_false") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockIsFollows = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getData() == MOCK_FOLLOWS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowed = MOCK_FOLLOWED;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Integer) not followed") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowed = MOCK_NO_FOLLOWED;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Wildcard)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_ENUM, *mockArgument1, *mockArgument2);

  FollowsAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
