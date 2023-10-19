#include <catch.hpp>

#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../mocks/MockPKBReader.h"
#include "../AbstractionTestUtils.h"
#include "FollowsStarAbstractionTestData.h"
#include "qps/abstraction/followsStarAbstraction/FollowsStarAbstraction.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Synonym)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockFollowsStarPairs = MOCK_FOLLOWS_STARS_PAIRS;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<SynonymArg> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_FOLLOWS_STARS_VECTOR);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockFollowedStar = MOCK_FOLLOWS_STARS_PAIRS;
  unique_ptr<SynonymArg> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<Integer> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_FOLLOWED_STAR_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Integer) not followed") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockFollowsStarPairs = MOCK_FOLLOWS_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_FOLLOWED_STAR_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockFollowsStar = MOCK_FOLLOWS_STARS_2;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.getDataAsStrings() == MOCK_FOLLOWS_STARS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Synonym)_no followed") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockFollowsStar = MOCK_FOLLOWS_STARS_2;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Wildcard)_no followed") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Integer)_true") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockIsFollowsStar = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Integer)_false") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockIsFollowsStar = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Synonym)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockFollowsStarPairs = MOCK_FOLLOWS_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_FOLLOWS_STARS_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Integer)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockFollowedStar = MOCK_FOLLOWS_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Integer) not followed") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Wildcard)") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  mockReader.mockFollowsStarPairs = MOCK_FOLLOWS_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Wildcard)_EMPTY") {
  MockPKBReader mockReader = MockPKBReader(MOCK_STORE);
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
