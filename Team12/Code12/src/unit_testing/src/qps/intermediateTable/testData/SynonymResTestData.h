#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "StringTestData.h"
#include "qps/common/Keywords.h"
#include "qps/intermediateTable/synonymRes/SynonymRes.h"

using std::string, std::pair, std::vector, std::set;

inline string SYNONYM_VAL_1 = "synonym value 1";
inline string SYNONYM_VAL_2 = "synonym value 2";
inline string SYNONYM_VAL_3 = "synonym value 3";
inline string SYNONYM_VAL_4 = "synonym value 4";

inline string SYNONYM_VAL_1B = "synonym value 1b";
inline string SYNONYM_VAL_2B = "synonym value 2b";

inline SynonymRes MOCK_DEFAULT_SYN_1 =
    SynonymRes::buildDefaultSynonym(SYNONYM_VAL_1);
inline SynonymRes MOCK_DEFAULT_SYN_2 =
    SynonymRes::buildDefaultSynonym(SYNONYM_VAL_2);
inline SynonymRes MOCK_DEFAULT_SYN_3 =
    SynonymRes::buildDefaultSynonym(SYNONYM_VAL_3);
inline SynonymRes MOCK_DEFAULT_SYN_4 =
    SynonymRes::buildDefaultSynonym(SYNONYM_VAL_4);

inline SynonymRes MOCK_CALLS_SYN_1 =
    SynonymRes::buildCallsSynonym(SYNONYM_VAL_1, SYNONYM_VAL_1B);
inline SynonymRes MOCK_CALLS_SYN_2 =
    SynonymRes::buildCallsSynonym(SYNONYM_VAL_2, SYNONYM_VAL_1B);
inline SynonymRes MOCK_CALLS_SYN_3 =
    SynonymRes::buildCallsSynonym(SYNONYM_VAL_1, SYNONYM_VAL_2B);
inline SynonymRes MOCK_CALLS_SYN_4 =
    SynonymRes::buildCallsSynonym(SYNONYM_VAL_4, SYNONYM_VAL_2B);

inline SynonymRes MOCK_CONSTANT_SYN_1 =
    SynonymRes::buildConstantSynonym(SYNONYM_VAL_1);
inline SynonymRes MOCK_CONSTANT_SYN_2 =
    SynonymRes::buildConstantSynonym(SYNONYM_VAL_2);
inline SynonymRes MOCK_CONSTANT_SYN_3 =
    SynonymRes::buildConstantSynonym(SYNONYM_VAL_3);
inline SynonymRes MOCK_CONSTANT_SYN_4 =
    SynonymRes::buildConstantSynonym(SYNONYM_VAL_4);

inline SynonymRes MOCK_PROC_SYN_1 = SynonymRes::buildProcSynonym(SYNONYM_VAL_1);
inline SynonymRes MOCK_PROC_SYN_2 = SynonymRes::buildProcSynonym(SYNONYM_VAL_2);
inline SynonymRes MOCK_PROC_SYN_3 = SynonymRes::buildProcSynonym(SYNONYM_VAL_3);
inline SynonymRes MOCK_PROC_SYN_4 = SynonymRes::buildProcSynonym(SYNONYM_VAL_4);

inline SynonymRes MOCK_STMT_SYN_1 = SynonymRes::buildStmtSynonym(SYNONYM_VAL_1);
inline SynonymRes MOCK_STMT_SYN_2 = SynonymRes::buildStmtSynonym(SYNONYM_VAL_2);
inline SynonymRes MOCK_STMT_SYN_3 = SynonymRes::buildStmtSynonym(SYNONYM_VAL_3);
inline SynonymRes MOCK_STMT_SYN_4 = SynonymRes::buildStmtSynonym(SYNONYM_VAL_4);

inline SynonymRes MOCK_VAR_SYN_1 = SynonymRes::buildVarSynonym(SYNONYM_VAL_1);
inline SynonymRes MOCK_VAR_SYN_2 = SynonymRes::buildVarSynonym(SYNONYM_VAL_2);
inline SynonymRes MOCK_VAR_SYN_3 = SynonymRes::buildVarSynonym(SYNONYM_VAL_3);
inline SynonymRes MOCK_VAR_SYN_4 = SynonymRes::buildVarSynonym(SYNONYM_VAL_4);
