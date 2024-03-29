#include <catch.hpp>

#include "../intermediateTable/testData/SynonymResTestData.h"
#include "../mocks/MockPKBReaderData.h"
#include "../mocks/mockReaders/BaseMockReader.h"
#include "qps/clause/selectClause/SelectClauseFactory.h"
#include "qps/clause/selectClause/selectTupleClause/SelectTupleClause.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

TEST_CASE("SelectClause - evaluate") {
  BaseMockReader mockPKB = BaseMockReader();
  unique_ptr<BaseSelectClause> selectClause =
      SelectClauseFactory::createSelectClause({});
  ClauseCache cache = ClauseCache{};
  IntermediateTable result = selectClause->evaluate(mockPKB, cache);
  REQUIRE(result.isTableWildcard());
}

TEST_CASE("SelectClause - getQuery - empty") {
  BaseMockReader mockPKB = BaseMockReader();
  unique_ptr<BaseSelectClause> selectClause =
      SelectClauseFactory::createSelectClause({});

  IntermediateTable emptyTable =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  REQUIRE(selectClause->getQueryResult(emptyTable) ==
          SelectBooleanClauseUtils::FALSE_RESULT);
}

TEST_CASE("SelectClause - getQuery - wildcard") {
  BaseMockReader mockPKB = BaseMockReader();
  unique_ptr<BaseSelectClause> selectClause =
      SelectClauseFactory::createSelectClause({});

  IntermediateTable table =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  REQUIRE(selectClause->getQueryResult(table) ==
          SelectBooleanClauseUtils::TRUE_RESULT);
}

TEST_CASE("SelectClause - getQuery - with_data") {
  BaseMockReader mockPKB = BaseMockReader();
  unique_ptr<BaseSelectClause> selectClause =
      SelectClauseFactory::createSelectClause({});

  IntermediateTable table =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_1, DOUBLE_COL_SYNONYM_RES_DATA);

  REQUIRE(selectClause->getQueryResult(table) ==
          SelectBooleanClauseUtils::TRUE_RESULT);
}
