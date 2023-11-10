#include <memory>
#include <catch.hpp>

#include "../../mocks/MockClause.h"
#include "../../mocks/mockReaders/MockDesignEntitiesReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/clauseDecorator/notDecorator/NotDecorator.h"
#include "qps/common/Keywords.h"

TEST_CASE("test_notDecorator_evaluate_0_synonym") {
  // Uses(ident, ident)

  string identVal1 = "1";
  string identVal2 = "hi";

  vector<string> synonymVec = {};

  Ident ident1 = Ident(identVal1);
  Ident ident2 = Ident(identVal2);

  unique_ptr<MockClause> mockClause = std::make_unique<MockClause>(synonymVec);

  IntermediateTable wrapeeClauseResult =
      IntermediateTableFactory::buildWildcardIntermediateTable();

  mockClause->mockAllArguments = {&ident1, &ident2};

  mockClause->mockEvaluate = wrapeeClauseResult;

  NotDecorator notDecorator = NotDecorator(std::move(mockClause));
  IntermediateTable intermediateTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  notDecorator.setCurrentTable(intermediateTable);

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  IntermediateTable actualTable = notDecorator.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_notDecorator_evaluate_1_synonym") {
  // Uses(AssignSyn, ident)

  string synonymVal = "yo";
  string identVal = "hi";

  vector<string> synonymVec = {synonymVal};

  SynonymArg syn1 = SynonymArg(synonymVal, ASSIGN_ENTITY);
  Ident ident1 = Ident(identVal);

  unique_ptr<MockClause> mockClause = std::make_unique<MockClause>(synonymVec);

  IntermediateTable wrapeeClauseResult =
      IntermediateTableFactory::buildSingleColTable(
          synonymVal, {SynonymResFactory::buildStmtSynonym("1"),
                       SynonymResFactory::buildStmtSynonym("2")});

  mockClause->mockAllArguments = {&syn1, &ident1};

  mockClause->mockEvaluate = wrapeeClauseResult;

  NotDecorator notDecorator = NotDecorator(std::move(mockClause));
  IntermediateTable intermediateTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  notDecorator.setCurrentTable(intermediateTable);

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockStatements = {"1", "2", "3", "4"};

  IntermediateTable actualTable = notDecorator.evaluate(mockPkbReader);

  vector<vector<string>> actualData = actualTable.getDataAsStrings();

  vector<vector<string>> expectedData = {{"3"}, {"4"}};

  REQUIRE(actualData == expectedData);
}

TEST_CASE("test_notDecorator_evaluate_2_synonym") {
  // Uses(AssignSyn, VarSyn)

  string synonymVal1 = "yo";
  string synonymVal2 = "yoyo";

  vector<string> synonymVec = {synonymVal1, synonymVal2};

  SynonymArg syn1 = SynonymArg(synonymVal1, ASSIGN_ENTITY);
  SynonymArg syn2 = SynonymArg(synonymVal2, VARIABLE_ENTITY);

  unique_ptr<MockClause> mockClause = std::make_unique<MockClause>(synonymVec);

  TableDataType mockClauseData = {{SynonymResFactory::buildStmtSynonym("1"),
                                   SynonymResFactory::buildVarSynonym("a")},
                                  {SynonymResFactory::buildStmtSynonym("2"),
                                   SynonymResFactory::buildVarSynonym("b")}};

  IntermediateTable wrapeeClauseResult =
      IntermediateTableFactory::buildIntermediateTable(
          {synonymVal1, synonymVal2}, mockClauseData);

  mockClause->mockAllArguments = {&syn1, &syn2};

  mockClause->mockEvaluate = wrapeeClauseResult;

  NotDecorator notDecorator = NotDecorator(std::move(mockClause));
  IntermediateTable intermediateTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  notDecorator.setCurrentTable(intermediateTable);

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockStatements = {"1", "2", "3", "4"};
  mockPkbReader.mockAllVariables = {"a", "b", "c"};

  IntermediateTable actualTable = notDecorator.evaluate(mockPkbReader);

  vector<vector<string>> actualData = actualTable.getDataAsStrings();

  vector<vector<string>> expectedData = {
      {"1", "b"}, {"1", "c"}, {"2", "a"}, {"2", "c"}, {"3", "a"},
      {"3", "b"}, {"3", "c"}, {"4", "a"}, {"4", "b"}, {"4", "c"}};

  REQUIRE(actualData == expectedData);
}
