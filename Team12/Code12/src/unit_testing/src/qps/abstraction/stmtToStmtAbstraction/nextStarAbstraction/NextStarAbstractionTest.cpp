#include <catch.hpp>

#include "../../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../../mocks/mockReaders/MockNextReader.h"
#include "../../AbstractionTestUtils.h"
#include "NextStarAbstractionTestData.h"
#include "qps/abstraction/stmtToStmtAbstraction/nextStarAbstraction/NextStarAbstraction.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"

TEST_CASE("NextStarAbstraction - Next*(Synonym, Synonym)_EMPTY") {
  MockNextReader mockReader = MockNextReader();
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  REQUIRE(resultTable.isTableEmpty());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Synonym)") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_NEXT_STAR_VECTORS);
  REQUIRE(resultTable.getColNames().size() == 2);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Integer)") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetPrevTStmts = MOCK_NEXT_STAR_FIRST_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_NEXT_STAR_FIRST_STMTS_2D);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Integer)_no_next") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetPrevTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Synonym, Wildcard)") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_NEXT_STAR_COL_1);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Synonym)") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetNextTStmts = MOCK_NEXT_STAR_SECOND_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.getDataAsStrings() == MOCK_NEXT_STAR_SECOND_STMTS_2D);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Synonym)_no_next") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetNextTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Wildcard)") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetNextTStmts = MOCK_NEXT_STAR_SECOND_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Wildcard)_no_next") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetNextTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Integer)_true") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockIsNextT = true;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Integer, Integer)_false") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockIsNextT = false;
  unique_ptr<AbstractArgument> mockArgument1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_2);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Synonym)") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.getDataAsStrings() == MOCK_NEXT_STAR_COL_2);
  REQUIRE(resultTable.getColNames().size() == 1);
  REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Integer)") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetPrevTStmts = MOCK_NEXT_STAR_FIRST_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Integer)_no_next") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetPrevTStmts = MOCK_NO_NEXT_STAR_STMTS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Wildcard)") {
  MockNextReader mockReader = MockNextReader();
  mockReader.mockGetNextTPairs = MOCK_NEXT_STAR_PAIRS;
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard());
  SynResConversionUtils::clearSynResCache();
}

TEST_CASE("NextStarAbstraction - Next*(Wildcard, Wildcard)_EMPTY") {
  MockNextReader mockReader = MockNextReader();
  unique_ptr<AbstractArgument> mockArgument1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> mockArgument2 = std::make_unique<Wildcard>();
  unique_ptr<AbstractionParams> abstractionParams = createMockAbstractionParams(
      mockReader, NEXT_STAR_ENUM, *mockArgument1, *mockArgument2);

  NextStarAbstraction abstraction(*abstractionParams);
  IntermediateTable resultTable = abstraction.evaluate();

  REQUIRE(resultTable.isTableWildcard() == false);
  REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
