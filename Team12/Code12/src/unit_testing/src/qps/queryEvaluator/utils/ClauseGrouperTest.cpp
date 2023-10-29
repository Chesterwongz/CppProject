#include <queue>
#include <catch.hpp>

#include "../../mocks/MockClause.h"
#include "../../mocks/MockPKBReaderData.h"
#include "qps/queryEvaluator/utils/clauseGrouper/ClauseGrouper.h"

TEST_CASE("ClauseGrouper - no_shared_synonyms") {
  vector<string> syn1And2 = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2};
  unique_ptr<Clause> mockClause1 = std::make_unique<MockClause>(syn1And2);
  vector<string> syn3And4 = {MOCK_SYNONYM_VALUE_3, MOCK_SYNONYM_VALUE_4};
  unique_ptr<Clause> mockClause2 = std::make_unique<MockClause>(syn3And4);
  vector<string> syn5And6 = {MOCK_SYNONYM_VALUE_5, MOCK_SYNONYM_VALUE_6};
  unique_ptr<Clause> mockClause3 = std::make_unique<MockClause>(syn5And6);
  vector<string> syn7And8 = {MOCK_SYNONYM_VALUE_7, MOCK_SYNONYM_VALUE_8};
  unique_ptr<Clause> mockClause4 = std::make_unique<MockClause>(syn7And8);

  ClauseUtil::ClauseList clauses {};

  clauses.push_back(std::move(mockClause1));
  clauses.push_back(std::move(mockClause2));
  clauses.push_back(std::move(mockClause3));
  clauses.push_back(std::move(mockClause4));

  unique_ptr<IClauseGrouper> grouper = std::make_unique<ClauseGrouper>(clauses);
  ClauseGroupQueue actualGroups = grouper->groupClauses();
  std::priority_queue<ClauseGroup> actualGroupsQueue = actualGroups.getQueue();

  REQUIRE(actualGroupsQueue.size() == 4);
}

TEST_CASE("ClauseGrouper - shared_synonyms_1_group") {
  vector<string> syn1And2 = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2};
  unique_ptr<Clause> mockClause1 = std::make_unique<MockClause>(syn1And2);
  vector<string> syn7And5 = {MOCK_SYNONYM_VALUE_7, MOCK_SYNONYM_VALUE_5};
  unique_ptr<Clause> mockClause2 = std::make_unique<MockClause>(syn7And5);
  vector<string> syn5And3 = {MOCK_SYNONYM_VALUE_5, MOCK_SYNONYM_VALUE_3};
  unique_ptr<Clause> mockClause3 = std::make_unique<MockClause>(syn5And3);
  vector<string> syn3And2 = {MOCK_SYNONYM_VALUE_3, MOCK_SYNONYM_VALUE_2};
  unique_ptr<Clause> mockClause4 = std::make_unique<MockClause>(syn3And2);

  ClauseUtil::ClauseList clauses {};

  clauses.push_back(std::move(mockClause1));
  clauses.push_back(std::move(mockClause2));
  clauses.push_back(std::move(mockClause3));
  clauses.push_back(std::move(mockClause4));

  unique_ptr<IClauseGrouper> grouper = std::make_unique<ClauseGrouper>(clauses);
  ClauseGroupQueue actualGroups = grouper->groupClauses();
  std::priority_queue<ClauseGroup> actualGroupsQueue = actualGroups.getQueue();

  REQUIRE(actualGroupsQueue.size() == 1);
}

TEST_CASE("ClauseGrouper - shared_synonyms_3_group") {
  vector<string> syn1And2 = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2};
  unique_ptr<Clause> mockClause1 = std::make_unique<MockClause>(syn1And2);
  vector<string> syn7And5 = {MOCK_SYNONYM_VALUE_7, MOCK_SYNONYM_VALUE_5};
  unique_ptr<Clause> mockClause2 = std::make_unique<MockClause>(syn7And5);
  vector<string> syn4And3 = {MOCK_SYNONYM_VALUE_4, MOCK_SYNONYM_VALUE_3};
  unique_ptr<Clause> mockClause3 = std::make_unique<MockClause>(syn4And3);
  vector<string> syn8And4 = {MOCK_SYNONYM_VALUE_8, MOCK_SYNONYM_VALUE_4};
  unique_ptr<Clause> mockClause4 = std::make_unique<MockClause>(syn8And4);

  ClauseUtil::ClauseList clauses {};

  clauses.push_back(std::move(mockClause1));
  clauses.push_back(std::move(mockClause2));
  clauses.push_back(std::move(mockClause3));
  clauses.push_back(std::move(mockClause4));

  unique_ptr<IClauseGrouper> grouper = std::make_unique<ClauseGrouper>(clauses);
  ClauseGroupQueue actualGroups = grouper->groupClauses();
  std::priority_queue<ClauseGroup> actualGroupsQueue = actualGroups.getQueue();

  REQUIRE(actualGroupsQueue.size() == 3);
}

TEST_CASE("ClauseGrouper - shared_synonyms_no_group") {
  ClauseUtil::ClauseList clauses {};
  unique_ptr<IClauseGrouper> grouper = std::make_unique<ClauseGrouper>(clauses);
  ClauseGroupQueue actualGroups = grouper->groupClauses();
  std::priority_queue<ClauseGroup> actualGroupsQueue = actualGroups.getQueue();

  REQUIRE(actualGroupsQueue.empty());
}
