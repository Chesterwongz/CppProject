#include <catch.hpp>

#include "../../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../../mocks/mockReaders/MockFollowsReader.h"
#include "../../AbstractionTestUtils.h"
#include "FollowsStarAbstractionTestData.h"
#include "qps/abstraction/stmtToStmtAbstraction/followsStarAbstraction/FollowsStarAbstraction.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Synonym)_EMPTY") {
  MockFollowsReader mockReader = MockFollowsReader();
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
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Synonym)") {
  MockFollowsReader mockReader = MockFollowsReader();
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
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Integer)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowedStar = MOCK_FOLLOWS_STARS_1;
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
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Integer) not followed") {
  MockFollowsReader mockReader = MockFollowsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Wildcard)") {
  MockFollowsReader mockReader = MockFollowsReader();
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
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Synonym)") {
  MockFollowsReader mockReader = MockFollowsReader();
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
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Synonym)_no followed") {
  MockFollowsReader mockReader = MockFollowsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Wildcard)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockIsFollowsStar = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Wildcard)_no followed") {
  MockFollowsReader mockReader = MockFollowsReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Integer)_true") {
  MockFollowsReader mockReader = MockFollowsReader();
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
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Integer)_false") {
  MockFollowsReader mockReader = MockFollowsReader();
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
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Synonym)") {
  MockFollowsReader mockReader = MockFollowsReader();
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
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Integer)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockIsFollowsStar = true;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Integer) not followed") {
  MockFollowsReader mockReader = MockFollowsReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Wildcard)") {
  MockFollowsReader mockReader = MockFollowsReader();
  mockReader.mockFollowsStarPairs = MOCK_FOLLOWS_STARS_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Wildcard)_EMPTY") {
  MockFollowsReader mockReader = MockFollowsReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, FOLLOWS_STAR_ENUM, *mockArgument1, *mockArgument2);

  FollowsStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
