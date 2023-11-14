#include <memory>
#include <vector>
#include <catch.hpp>

#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../../intermediateTable/testData/SynonymResTestData.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/clauseCache/ClauseCache.h"
#include "qps/clause/patternClause/AssignPatternClause.h"
#include "qps/clause/patternClause/IfPatternClause.h"
#include "qps/clause/patternClause/WhilePatternClause.h"
#include "qps/clause/selectClause/BaseSelectClause.h"
#include "qps/clause/selectClause/selectTupleClause/SelectTupleClause.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/clause/withClause/WithClause.h"
#include "qps/clause/clauseDecorator/notDecorator/NotDecorator.h"

using std::unique_ptr;

namespace ClauseCacheTestData {
string SYNONYM_VAL_1 = "syn1";
string SYNONYM_VAL_2 = "syn2";

string INTEGER_VAL_1 = "1";
string INTEGER_VAL_2 = "2";

IntermediateTable t1 = IntermediateTableFactory::buildIntermediateTable(
    SYNONYM_RES_MULTI_COL_NAME_1, MULTI_COL_SYNONYM_RES_DATA_1);

IntermediateTable t2 = IntermediateTableFactory::buildIntermediateTable(
    SYNONYM_RES_MULTI_COL_NAME_2, MULTI_COL_SYNONYM_RES_DATA_2);
}  // namespace ClauseCacheTestData

// ==== SAME CLAUSE ====
TEST_CASE("ClauseCache - same_clause - SuchThatClause") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> suchThat1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> suchThat1Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause1 = std::make_unique<SuchThatClause>(
      FOLLOWS_STAR_ENUM, std::move(suchThat1Arg1), std::move(suchThat1Arg2));

  unique_ptr<SynonymArg> suchThat2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> suchThat2Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause2 = std::make_unique<SuchThatClause>(
      FOLLOWS_STAR_ENUM, std::move(suchThat2Arg1), std::move(suchThat2Arg2));

  cache.saveToCache(suchThatClause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE(cache.isCacheHit(suchThatClause2->getKey()));

  IntermediateTable cacheRes = cache.getResFromCache(suchThatClause2->getKey());
  REQUIRE(isTableDataSame(cacheRes.getTableData(),
                          ClauseCacheTestData::t1.getTableData()));
}

TEST_CASE("ClauseCache - same_clause - BaseSelectClause") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> select1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> select1Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect1 {};
  synonymsToSelect1.emplace_back(std::move(select1Arg1));
  synonymsToSelect1.emplace_back(std::move(select1Arg2));

  unique_ptr<BaseSelectClause> baseSelectClause1 =
      std::make_unique<SelectTupleClause>(std::move(synonymsToSelect1));

  unique_ptr<SynonymArg> select2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> select2Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  SynonymsToSelect synonymsToSelect2 {};
  synonymsToSelect2.emplace_back(std::move(select2Arg1));
  synonymsToSelect2.emplace_back(std::move(select2Arg2));

  unique_ptr<BaseSelectClause> baseSelectClause2 =
      std::make_unique<SelectTupleClause>(std::move(synonymsToSelect2));

  cache.saveToCache(baseSelectClause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE(cache.isCacheHit(baseSelectClause2->getKey()));

  IntermediateTable cacheRes =
      cache.getResFromCache(baseSelectClause2->getKey());
  REQUIRE(isTableDataSame(cacheRes.getTableData(),
                          ClauseCacheTestData::t1.getTableData()));
}

TEST_CASE("ClauseCache - same_clause - WithClause") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> with1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> with1Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<WithClause> withClause1 =
      std::make_unique<WithClause>(std::move(with1Arg1), std::move(with1Arg2));

  unique_ptr<SynonymArg> with2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> with2Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<WithClause> withClause2 =
      std::make_unique<WithClause>(std::move(with2Arg1), std::move(with2Arg2));

  cache.saveToCache(withClause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE(cache.isCacheHit(withClause2->getKey()));

  IntermediateTable cacheRes = cache.getResFromCache(withClause2->getKey());
  REQUIRE(isTableDataSame(cacheRes.getTableData(),
                          ClauseCacheTestData::t1.getTableData()));
}

TEST_CASE("ClauseCache - same_clause - AssignPatternClause") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> assign1syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> assign1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<Integer> assign1arg2 =
      std::make_unique<Integer>(ClauseCacheTestData::INTEGER_VAL_1);
  unique_ptr<AssignPatternClause> clause1 =
      std::make_unique<AssignPatternClause>(std::move(assign1syn1),
                                            std::move(assign1Arg1),
                                            std::move(assign1arg2), true);

  unique_ptr<SynonymArg> assign2syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> assign2arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<Integer> assign2arg2 =
      std::make_unique<Integer>(ClauseCacheTestData::INTEGER_VAL_1);
  unique_ptr<AssignPatternClause> clause2 =
      std::make_unique<AssignPatternClause>(std::move(assign2syn1),
                                            std::move(assign2arg1),
                                            std::move(assign2arg2), true);

  cache.saveToCache(clause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE(cache.isCacheHit(clause2->getKey()));

  IntermediateTable cacheRes = cache.getResFromCache(clause2->getKey());
  REQUIRE(isTableDataSame(cacheRes.getTableData(),
                          ClauseCacheTestData::t1.getTableData()));
}

TEST_CASE("ClauseCache - same_clause - IfPatternClause") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> if1syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> if1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<IfPatternClause> clause1 =
      std::make_unique<IfPatternClause>(std::move(if1syn1), std::move(if1Arg1));

  unique_ptr<SynonymArg> if2syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> if2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<IfPatternClause> clause2 =
      std::make_unique<IfPatternClause>(std::move(if2syn1), std::move(if2Arg1));

  cache.saveToCache(clause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE(cache.isCacheHit(clause2->getKey()));

  IntermediateTable cacheRes = cache.getResFromCache(clause2->getKey());
  REQUIRE(isTableDataSame(cacheRes.getTableData(),
                          ClauseCacheTestData::t1.getTableData()));
}

TEST_CASE("ClauseCache - same_clause - WhilePatternClause") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> while1syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> while1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<WhilePatternClause> clause1 = std::make_unique<WhilePatternClause>(
      std::move(while1syn1), std::move(while1Arg1));

  unique_ptr<SynonymArg> while2syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> while2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<WhilePatternClause> clause2 = std::make_unique<WhilePatternClause>(
      std::move(while2syn1), std::move(while2Arg1));

  cache.saveToCache(clause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE(cache.isCacheHit(clause2->getKey()));

  IntermediateTable cacheRes = cache.getResFromCache(clause2->getKey());
  REQUIRE(isTableDataSame(cacheRes.getTableData(),
                          ClauseCacheTestData::t1.getTableData()));
}

// ==== DIFF CLAUSE - NOT ====
TEST_CASE("ClauseCache - normal_vs_not - SuchThatClause") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> suchThat1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> suchThat1Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause1 = std::make_unique<SuchThatClause>(
      FOLLOWS_STAR_ENUM, std::move(suchThat1Arg1), std::move(suchThat1Arg2));

  unique_ptr<SynonymArg> suchThat2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> suchThat2Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause2 = std::make_unique<SuchThatClause>(
      FOLLOWS_STAR_ENUM, std::move(suchThat2Arg1), std::move(suchThat2Arg2));
  unique_ptr<BaseClause> notClause =
      std::make_unique<NotDecorator>(std::move(suchThatClause2));

  cache.saveToCache(suchThatClause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE_FALSE(cache.isCacheHit(notClause->getKey()));
  REQUIRE(cache.isCacheHit(suchThatClause1->getKey()));
}

TEST_CASE("ClauseCache - normal_vs_not - WithClause") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> with1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> with1Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<WithClause> withClause1 =
      std::make_unique<WithClause>(std::move(with1Arg1), std::move(with1Arg2));

  unique_ptr<SynonymArg> with2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> with2Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<WithClause> withClause2 =
      std::make_unique<WithClause>(std::move(with2Arg1), std::move(with2Arg2));
  unique_ptr<BaseClause> notClause =
      std::make_unique<NotDecorator>(std::move(withClause2));

  cache.saveToCache(withClause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE_FALSE(cache.isCacheHit(notClause->getKey()));
  REQUIRE(cache.isCacheHit(withClause1->getKey()));
}

TEST_CASE("ClauseCache - normal_vs_not - AssignPatternClause") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> assign1syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> assign1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<Integer> assign1arg2 =
      std::make_unique<Integer>(ClauseCacheTestData::INTEGER_VAL_1);
  unique_ptr<AssignPatternClause> clause1 =
      std::make_unique<AssignPatternClause>(std::move(assign1syn1),
                                            std::move(assign1Arg1),
                                            std::move(assign1arg2), true);

  unique_ptr<SynonymArg> assign2syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> assign2arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<Integer> assign2arg2 =
      std::make_unique<Integer>(ClauseCacheTestData::INTEGER_VAL_1);
  unique_ptr<AssignPatternClause> clause2 =
      std::make_unique<AssignPatternClause>(std::move(assign2syn1),
                                            std::move(assign2arg1),
                                            std::move(assign2arg2), true);
  unique_ptr<BaseClause> notClause =
      std::make_unique<NotDecorator>(std::move(clause2));

  cache.saveToCache(clause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE_FALSE(cache.isCacheHit(notClause->getKey()));
  REQUIRE(cache.isCacheHit(clause1->getKey()));
}

TEST_CASE("ClauseCache - normal_vs_not - IfPatternClause") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> if1syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> if1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<IfPatternClause> clause1 =
      std::make_unique<IfPatternClause>(std::move(if1syn1), std::move(if1Arg1));

  unique_ptr<SynonymArg> if2syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> if2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<IfPatternClause> clause2 =
      std::make_unique<IfPatternClause>(std::move(if2syn1), std::move(if2Arg1));
  unique_ptr<BaseClause> notClause =
      std::make_unique<NotDecorator>(std::move(clause2));

  cache.saveToCache(clause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE_FALSE(cache.isCacheHit(notClause->getKey()));
  REQUIRE(cache.isCacheHit(clause1->getKey()));
}

TEST_CASE("ClauseCache - normal_vs_not - WhilePatternClause") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> while1syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> while1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<WhilePatternClause> clause1 = std::make_unique<WhilePatternClause>(
      std::move(while1syn1), std::move(while1Arg1));

  unique_ptr<SynonymArg> while2syn1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> while2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<WhilePatternClause> clause2 = std::make_unique<WhilePatternClause>(
      std::move(while2syn1), std::move(while2Arg1));
  unique_ptr<BaseClause> notClause =
      std::make_unique<NotDecorator>(std::move(clause2));

  cache.saveToCache(clause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE_FALSE(cache.isCacheHit(notClause->getKey()));
  REQUIRE(cache.isCacheHit(clause1->getKey()));
}

// ==== DIFF CLAUSE - diff clause type ====
TEST_CASE("ClauseCache - diff_clause_type_with_same_arg") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> suchThatArg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> suchThatArg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_STAR_ENUM, std::move(suchThatArg1), std::move(suchThatArg2));

  unique_ptr<SynonymArg> withArg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> withArg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<WithClause> withClause =
      std::make_unique<WithClause>(std::move(withArg1), std::move(withArg2));

  cache.saveToCache(suchThatClause->getKey(), ClauseCacheTestData::t1);
  REQUIRE_FALSE(cache.isCacheHit(withClause->getKey()));

  cache.saveToCache(withClause->getKey(), ClauseCacheTestData::t2);
  REQUIRE(cache.isCacheHit(withClause->getKey()));

  IntermediateTable withClauseCacheRes =
      cache.getResFromCache(withClause->getKey());
  IntermediateTable suchThatClauseCacheRes =
      cache.getResFromCache(suchThatClause->getKey());

  REQUIRE_FALSE(isTableDataSame(suchThatClauseCacheRes.getTableData(),
                                withClauseCacheRes.getTableData()));
  REQUIRE(isTableDataSame(suchThatClauseCacheRes.getTableData(),
                          ClauseCacheTestData::t1.getTableData()));
  REQUIRE(isTableDataSame(withClauseCacheRes.getTableData(),
                          ClauseCacheTestData::t2.getTableData()));
}

// ==== DIFF CLAUSE - diff args ====
TEST_CASE("ClauseCache - same_clause_type_same_arg_val_with_diff_arg_entity") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> suchThat1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> suchThat1Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause1 = std::make_unique<SuchThatClause>(
      FOLLOWS_STAR_ENUM, std::move(suchThat1Arg1), std::move(suchThat1Arg2));

  unique_ptr<SynonymArg> suchThat2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> suchThat2Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause2 = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(suchThat2Arg1), std::move(suchThat2Arg2));

  cache.saveToCache(suchThatClause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE_FALSE(cache.isCacheHit(suchThatClause2->getKey()));

  cache.saveToCache(suchThatClause2->getKey(), ClauseCacheTestData::t2);
  REQUIRE(cache.isCacheHit(suchThatClause2->getKey()));

  IntermediateTable suchThatClauseCacheRes1 =
      cache.getResFromCache(suchThatClause1->getKey());
  IntermediateTable suchThatClauseCacheRes2 =
      cache.getResFromCache(suchThatClause2->getKey());

  REQUIRE_FALSE(isTableDataSame(suchThatClauseCacheRes1.getTableData(),
                                suchThatClauseCacheRes2.getTableData()));
  REQUIRE(isTableDataSame(suchThatClauseCacheRes1.getTableData(),
                          ClauseCacheTestData::t1.getTableData()));
  REQUIRE(isTableDataSame(suchThatClauseCacheRes2.getTableData(),
                          ClauseCacheTestData::t2.getTableData()));
}

TEST_CASE("ClauseCache - same_clause_type_same_arg_entity_with_diff_arg_val") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> suchThat1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> suchThat1Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause1 = std::make_unique<SuchThatClause>(
      FOLLOWS_STAR_ENUM, std::move(suchThat1Arg1), std::move(suchThat1Arg2));

  unique_ptr<SynonymArg> suchThat2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> suchThat2Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause2 = std::make_unique<SuchThatClause>(
      FOLLOWS_STAR_ENUM, std::move(suchThat2Arg1), std::move(suchThat2Arg2));

  cache.saveToCache(suchThatClause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE_FALSE(cache.isCacheHit(suchThatClause2->getKey()));

  cache.saveToCache(suchThatClause2->getKey(), ClauseCacheTestData::t2);
  REQUIRE(cache.isCacheHit(suchThatClause2->getKey()));

  IntermediateTable suchThatClauseCacheRes1 =
      cache.getResFromCache(suchThatClause1->getKey());
  IntermediateTable suchThatClauseCacheRes2 =
      cache.getResFromCache(suchThatClause2->getKey());

  REQUIRE_FALSE(isTableDataSame(suchThatClauseCacheRes1.getTableData(),
                                suchThatClauseCacheRes2.getTableData()));
  REQUIRE(isTableDataSame(suchThatClauseCacheRes1.getTableData(),
                          ClauseCacheTestData::t1.getTableData()));
  REQUIRE(isTableDataSame(suchThatClauseCacheRes2.getTableData(),
                          ClauseCacheTestData::t2.getTableData()));
}

TEST_CASE("ClauseCache - same_clause_type_same_arg_entity_with_diff_arg_type") {
  ClauseCache cache {};
  unique_ptr<SynonymArg> suchThat1Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> suchThat1Arg2 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause1 = std::make_unique<SuchThatClause>(
      FOLLOWS_STAR_ENUM, std::move(suchThat1Arg1), std::move(suchThat1Arg2));

  unique_ptr<SynonymArg> suchThat2Arg1 = std::make_unique<SynonymArg>(
      ClauseCacheTestData::SYNONYM_VAL_1, ASSIGN_ENTITY);
  unique_ptr<Ident> suchThat2Arg2 =
      std::make_unique<Ident>(ClauseCacheTestData::SYNONYM_VAL_2);
  unique_ptr<SuchThatClause> suchThatClause2 = std::make_unique<SuchThatClause>(
      FOLLOWS_STAR_ENUM, std::move(suchThat2Arg1), std::move(suchThat2Arg2));

  cache.saveToCache(suchThatClause1->getKey(), ClauseCacheTestData::t1);
  REQUIRE_FALSE(cache.isCacheHit(suchThatClause2->getKey()));

  cache.saveToCache(suchThatClause2->getKey(), ClauseCacheTestData::t2);
  REQUIRE(cache.isCacheHit(suchThatClause2->getKey()));

  IntermediateTable suchThatClauseCacheRes1 =
      cache.getResFromCache(suchThatClause1->getKey());
  IntermediateTable suchThatClauseCacheRes2 =
      cache.getResFromCache(suchThatClause2->getKey());

  REQUIRE_FALSE(isTableDataSame(suchThatClauseCacheRes1.getTableData(),
                                suchThatClauseCacheRes2.getTableData()));
  REQUIRE(isTableDataSame(suchThatClauseCacheRes1.getTableData(),
                          ClauseCacheTestData::t1.getTableData()));
  REQUIRE(isTableDataSame(suchThatClauseCacheRes2.getTableData(),
                          ClauseCacheTestData::t2.getTableData()));
}
