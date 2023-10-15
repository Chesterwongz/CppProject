#include <catch.hpp>

#include "../testData/SynonymResTestData.h"
#include "qps/intermediateTable/synonymRes/SynonymRes.h"

TEST_CASE("SynonymRes - operator== -between_same_kind") {
  // between default synonyms - diff default value
  REQUIRE(MOCK_DEFAULT_SYN_1 == SynonymRes::buildDefaultSynonym(SYNONYM_VAL_1));
  REQUIRE_FALSE(MOCK_DEFAULT_SYN_1 == MOCK_DEFAULT_SYN_2);

  // between calls synonyms
  REQUIRE(MOCK_CALLS_SYN_1 ==
          SynonymRes::buildCallsSynonym(SYNONYM_VAL_1, SYNONYM_VAL_1B));
  //  - diff call stmtNum but same procName
  REQUIRE_FALSE(MOCK_CALLS_SYN_1 == MOCK_CALLS_SYN_2);
  //  - diff call procName but same stmtNum
  REQUIRE_FALSE(MOCK_CALLS_SYN_1 == MOCK_CALLS_SYN_3);
  //  - diff call procName and diff stmtNum
  REQUIRE_FALSE(MOCK_CALLS_SYN_1 == MOCK_CALLS_SYN_4);

  // between constant synonyms - diff constant value
  REQUIRE(MOCK_CONSTANT_SYN_1 ==
          SynonymRes::buildConstantSynonym(SYNONYM_VAL_1));
  REQUIRE_FALSE(MOCK_CONSTANT_SYN_1 == MOCK_CONSTANT_SYN_2);

  // between proc synonyms - diff proc procName
  REQUIRE(MOCK_PROC_SYN_1 == SynonymRes::buildProcSynonym(SYNONYM_VAL_1));
  REQUIRE_FALSE(MOCK_PROC_SYN_1 == MOCK_PROC_SYN_2);

  // between stmt synonyms - diff stmt stmtNum
  REQUIRE(MOCK_STMT_SYN_1 == SynonymRes::buildStmtSynonym(SYNONYM_VAL_1));
  REQUIRE_FALSE(MOCK_STMT_SYN_1 == MOCK_STMT_SYN_2);

  // diff var stmtNum
  REQUIRE(MOCK_VAR_SYN_1 == SynonymRes::buildVarSynonym(SYNONYM_VAL_1));
  REQUIRE_FALSE(MOCK_VAR_SYN_1 == MOCK_VAR_SYN_2);
}

TEST_CASE("SynonymRes - operator== -between_diff_kind") {
  REQUIRE_FALSE(MOCK_DEFAULT_SYN_1 == MOCK_CALLS_SYN_1);
  REQUIRE_FALSE(MOCK_DEFAULT_SYN_1 == MOCK_CONSTANT_SYN_1);
  REQUIRE_FALSE(MOCK_DEFAULT_SYN_1 == MOCK_PROC_SYN_1);
  REQUIRE_FALSE(MOCK_DEFAULT_SYN_1 == MOCK_STMT_SYN_1);
  REQUIRE_FALSE(MOCK_DEFAULT_SYN_1 == MOCK_VAR_SYN_1);

  REQUIRE_FALSE(MOCK_CALLS_SYN_1 == MOCK_CONSTANT_SYN_1);
  REQUIRE_FALSE(MOCK_CALLS_SYN_1 == MOCK_PROC_SYN_1);
  REQUIRE_FALSE(MOCK_CALLS_SYN_1 == MOCK_STMT_SYN_1);
  REQUIRE_FALSE(MOCK_CALLS_SYN_1 == MOCK_VAR_SYN_1);

  REQUIRE_FALSE(MOCK_CONSTANT_SYN_1 == MOCK_PROC_SYN_1);
  REQUIRE_FALSE(MOCK_CONSTANT_SYN_1 == MOCK_STMT_SYN_1);
  REQUIRE_FALSE(MOCK_CONSTANT_SYN_1 == MOCK_VAR_SYN_1);

  REQUIRE_FALSE(MOCK_PROC_SYN_1 == MOCK_STMT_SYN_1);
  REQUIRE_FALSE(MOCK_PROC_SYN_1 == MOCK_VAR_SYN_1);

  REQUIRE_FALSE(MOCK_STMT_SYN_1 == MOCK_VAR_SYN_1);
}

TEST_CASE("SynonymRes - operator!= -between_same_kind") {
  // between default synonyms - diff default value
  REQUIRE(MOCK_DEFAULT_SYN_1 != MOCK_DEFAULT_SYN_2);
  REQUIRE_FALSE(MOCK_DEFAULT_SYN_1 != MOCK_DEFAULT_SYN_1);

  // between calls synonyms - diff call stmtNum but same procName
  REQUIRE(MOCK_CALLS_SYN_1 != MOCK_CALLS_SYN_2);
  REQUIRE_FALSE(MOCK_CALLS_SYN_1 != MOCK_CALLS_SYN_1);
  REQUIRE_FALSE(MOCK_CALLS_SYN_2 != MOCK_CALLS_SYN_2);

  // between calls synonyms - diff call procName but same stmtNum
  REQUIRE(MOCK_CALLS_SYN_1 != MOCK_CALLS_SYN_3);
  REQUIRE_FALSE(MOCK_CALLS_SYN_1 != MOCK_CALLS_SYN_1);

  // between calls synonyms - diff call procName and diff stmtNum
  REQUIRE(MOCK_CALLS_SYN_1 != MOCK_CALLS_SYN_4);
  REQUIRE_FALSE(MOCK_CALLS_SYN_1 != MOCK_CALLS_SYN_1);

  // between constant synonyms - diff constant value
  REQUIRE(MOCK_CONSTANT_SYN_1 != MOCK_CONSTANT_SYN_2);
  REQUIRE_FALSE(MOCK_CONSTANT_SYN_1 != MOCK_CONSTANT_SYN_1);

  // between proc synonyms - diff proc procName
  REQUIRE(MOCK_PROC_SYN_1 != MOCK_PROC_SYN_2);
  REQUIRE_FALSE(MOCK_PROC_SYN_1 != MOCK_PROC_SYN_1);

  // between stmt synonyms - diff stmt stmtNum
  REQUIRE(MOCK_STMT_SYN_1 != MOCK_STMT_SYN_2);
  REQUIRE_FALSE(MOCK_STMT_SYN_1 != MOCK_STMT_SYN_1);

  // diff var stmtNum
  REQUIRE(MOCK_VAR_SYN_1 != MOCK_VAR_SYN_2);
  REQUIRE_FALSE(MOCK_VAR_SYN_1 != MOCK_VAR_SYN_1);
}

TEST_CASE("SynonymRes - operator!= -between_diff_kind") {
  REQUIRE(MOCK_DEFAULT_SYN_1 != MOCK_CALLS_SYN_1);
  REQUIRE(MOCK_DEFAULT_SYN_1 != MOCK_CONSTANT_SYN_1);
  REQUIRE(MOCK_DEFAULT_SYN_1 != MOCK_PROC_SYN_1);
  REQUIRE(MOCK_DEFAULT_SYN_1 != MOCK_STMT_SYN_1);
  REQUIRE(MOCK_DEFAULT_SYN_1 != MOCK_VAR_SYN_1);

  REQUIRE(MOCK_CALLS_SYN_1 != MOCK_CONSTANT_SYN_1);
  REQUIRE(MOCK_CALLS_SYN_1 != MOCK_PROC_SYN_1);
  REQUIRE(MOCK_CALLS_SYN_1 != MOCK_STMT_SYN_1);
  REQUIRE(MOCK_CALLS_SYN_1 != MOCK_VAR_SYN_1);

  REQUIRE(MOCK_CONSTANT_SYN_1 != MOCK_PROC_SYN_1);
  REQUIRE(MOCK_CONSTANT_SYN_1 != MOCK_STMT_SYN_1);
  REQUIRE(MOCK_CONSTANT_SYN_1 != MOCK_VAR_SYN_1);

  REQUIRE(MOCK_PROC_SYN_1 != MOCK_STMT_SYN_1);
  REQUIRE(MOCK_PROC_SYN_1 != MOCK_VAR_SYN_1);

  REQUIRE(MOCK_STMT_SYN_1 != MOCK_VAR_SYN_1);
}
