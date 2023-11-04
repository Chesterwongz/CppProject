#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "StringTestData.h"
#include "qps/common/Keywords.h"
#include "qps/intermediateTable/synonymRes/SynonymRes.h"
#include "qps/intermediateTable/synonymRes/SynonymResFactory.h"

using std::string, std::pair, std::vector, std::set;

inline string SYNONYM_VAL_1 = "synonym value 1";
inline string SYNONYM_VAL_2 = "synonym value 2";
inline string SYNONYM_VAL_3 = "synonym value 3";
inline string SYNONYM_VAL_4 = "synonym value 4";
inline vector<vector<string>> MOCK_SYNONYM_RES_VALUES_VECTOR_2D = {
    {SYNONYM_VAL_1}, {SYNONYM_VAL_2}, {SYNONYM_VAL_3}, {SYNONYM_VAL_4}};

inline string SYNONYM_VAL_1B = "synonym value 1b";
inline string SYNONYM_VAL_2B = "synonym value 2b";
inline string SYNONYM_VAL_3B = "synonym value 3b";

inline SynonymRes& MOCK_DEFAULT_SYN_1 =
    SynonymResFactory::buildDefaultSynonym(SYNONYM_VAL_1);
inline SynonymRes& MOCK_DEFAULT_SYN_2 =
    SynonymResFactory::buildDefaultSynonym(SYNONYM_VAL_2);
inline SynonymRes& MOCK_DEFAULT_SYN_3 =
    SynonymResFactory::buildDefaultSynonym(SYNONYM_VAL_3);
inline SynonymRes& MOCK_DEFAULT_SYN_4 =
    SynonymResFactory::buildDefaultSynonym(SYNONYM_VAL_4);

inline SynonymRes& MOCK_CALLS_SYN_1 =
    SynonymResFactory::buildCallsSynonym(SYNONYM_VAL_1, SYNONYM_VAL_1B);
inline SynonymRes& MOCK_CALLS_SYN_2 =
    SynonymResFactory::buildCallsSynonym(SYNONYM_VAL_2, SYNONYM_VAL_1B);
inline SynonymRes& MOCK_CALLS_SYN_3 =
    SynonymResFactory::buildCallsSynonym(SYNONYM_VAL_1, SYNONYM_VAL_2B);
inline SynonymRes& MOCK_CALLS_SYN_4 =
    SynonymResFactory::buildCallsSynonym(SYNONYM_VAL_4, SYNONYM_VAL_2B);

inline SynonymRes& MOCK_CONSTANT_SYN_1 =
    SynonymResFactory::buildConstantSynonym(SYNONYM_VAL_1);
inline SynonymRes& MOCK_CONSTANT_SYN_2 =
    SynonymResFactory::buildConstantSynonym(SYNONYM_VAL_2);
inline SynonymRes& MOCK_CONSTANT_SYN_3 =
    SynonymResFactory::buildConstantSynonym(SYNONYM_VAL_3);
inline SynonymRes& MOCK_CONSTANT_SYN_4 =
    SynonymResFactory::buildConstantSynonym(SYNONYM_VAL_4);

inline SynonymRes& MOCK_PRINT_SYN_1 =
    SynonymResFactory::buildPrintSynonym(SYNONYM_VAL_1, SYNONYM_VAL_1B);
inline SynonymRes& MOCK_PRINT_SYN_2 =
    SynonymResFactory::buildPrintSynonym(SYNONYM_VAL_2, SYNONYM_VAL_1B);
inline SynonymRes& MOCK_PRINT_SYN_3 =
    SynonymResFactory::buildPrintSynonym(SYNONYM_VAL_3, SYNONYM_VAL_2B);
inline SynonymRes& MOCK_PRINT_SYN_4 =
    SynonymResFactory::buildPrintSynonym(SYNONYM_VAL_4, SYNONYM_VAL_2B);
inline SynonymRes& MOCK_PRINT_SYN_5 =
    SynonymResFactory::buildPrintSynonym(SYNONYM_VAL_4, SYNONYM_VAL_3B);
inline vector<std::reference_wrapper<SynonymRes>>
    MOCK_PRINT_SYNONYM_RES_VECTOR = {MOCK_PRINT_SYN_1, MOCK_PRINT_SYN_2,
                                     MOCK_PRINT_SYN_3, MOCK_PRINT_SYN_4};
inline vector<vector<std::reference_wrapper<SynonymRes>>>
    MOCK_PRINT_SYNONYM_RES_VECTOR_2D = {{MOCK_PRINT_SYN_1},
                                        {MOCK_PRINT_SYN_2},
                                        {MOCK_PRINT_SYN_3},
                                        {MOCK_PRINT_SYN_4}};

inline SynonymRes& MOCK_PROC_SYN_1 =
    SynonymResFactory::buildProcSynonym(SYNONYM_VAL_1);
inline SynonymRes& MOCK_PROC_SYN_2 =
    SynonymResFactory::buildProcSynonym(SYNONYM_VAL_2);
inline SynonymRes& MOCK_PROC_SYN_3 =
    SynonymResFactory::buildProcSynonym(SYNONYM_VAL_3);
inline SynonymRes& MOCK_PROC_SYN_4 =
    SynonymResFactory::buildProcSynonym(SYNONYM_VAL_4);

inline SynonymRes& MOCK_STMT_SYN_1 =
    SynonymResFactory::buildStmtSynonym(SYNONYM_VAL_1);
inline SynonymRes& MOCK_STMT_SYN_2 =
    SynonymResFactory::buildStmtSynonym(SYNONYM_VAL_2);
inline SynonymRes& MOCK_STMT_SYN_3 =
    SynonymResFactory::buildStmtSynonym(SYNONYM_VAL_3);
inline SynonymRes& MOCK_STMT_SYN_4 =
    SynonymResFactory::buildStmtSynonym(SYNONYM_VAL_4);

inline SynonymRes& MOCK_VAR_SYN_1 =
    SynonymResFactory::buildVarSynonym(SYNONYM_VAL_1);
inline SynonymRes& MOCK_VAR_SYN_2 =
    SynonymResFactory::buildVarSynonym(SYNONYM_VAL_2);
inline SynonymRes& MOCK_VAR_SYN_3 =
    SynonymResFactory::buildVarSynonym(SYNONYM_VAL_3);
inline SynonymRes& MOCK_VAR_SYN_4 =
    SynonymResFactory::buildVarSynonym(SYNONYM_VAL_4);

inline vector<string> SYNONYM_RES_COL_NAME_1 = {"default", "calls"};
inline vector<vector<std::reference_wrapper<SynonymRes>>>
    DOUBLE_COL_SYNONYM_RES_DATA = {
        {MOCK_DEFAULT_SYN_1, MOCK_CALLS_SYN_1},
        {MOCK_DEFAULT_SYN_2, MOCK_CALLS_SYN_2},
        {MOCK_DEFAULT_SYN_3, MOCK_CALLS_SYN_3},
        {MOCK_DEFAULT_SYN_4, MOCK_CALLS_SYN_4},
};

inline vector<string> SYNONYM_RES_COL_NAME_2 = {"constant", "print"};
inline vector<vector<std::reference_wrapper<SynonymRes>>>
    DOUBLE_COL_SYNONYM_RES_DATA_2 = {
        {MOCK_CONSTANT_SYN_1, MOCK_PRINT_SYN_1},
        {MOCK_CONSTANT_SYN_2, MOCK_PRINT_SYN_2},
        {MOCK_CONSTANT_SYN_3, MOCK_PRINT_SYN_3},
        {MOCK_CONSTANT_SYN_4, MOCK_PRINT_SYN_4},
};

inline vector<string> SYNONYM_RES_COL_NAME_3 = {"constant", "print"};
inline vector<vector<std::reference_wrapper<SynonymRes>>>
    DOUBLE_COL_SYNONYM_RES_DATA_3 = {
        {MOCK_CONSTANT_SYN_1, MOCK_PRINT_SYN_5},
        {MOCK_CONSTANT_SYN_2, MOCK_PRINT_SYN_2},
};

inline vector<string> SYNONYM_RES_MULTI_COL_NAME_1 = {
    "default", "calls", "constant", "stmt", "print"};
inline vector<vector<std::reference_wrapper<SynonymRes>>>
    MULTI_COL_SYNONYM_RES_DATA_1 = {
        {MOCK_DEFAULT_SYN_1, MOCK_CALLS_SYN_1, MOCK_CONSTANT_SYN_1,
         MOCK_STMT_SYN_1, MOCK_PRINT_SYN_1},
        {MOCK_DEFAULT_SYN_2, MOCK_CALLS_SYN_2, MOCK_CONSTANT_SYN_2,
         MOCK_STMT_SYN_2, MOCK_PRINT_SYN_2},
        {MOCK_DEFAULT_SYN_3, MOCK_CALLS_SYN_3, MOCK_CONSTANT_SYN_3,
         MOCK_STMT_SYN_3, MOCK_PRINT_SYN_3},
        {MOCK_DEFAULT_SYN_4, MOCK_CALLS_SYN_4, MOCK_CONSTANT_SYN_4,
         MOCK_STMT_SYN_4, MOCK_PRINT_SYN_4},
};

inline vector<string> SYNONYM_RES_MULTI_COL_NAME_2 = {"constant", "proc", "var",
                                                      "print"};
inline vector<vector<std::reference_wrapper<SynonymRes>>>
    MULTI_COL_SYNONYM_RES_DATA_2 = {
        {MOCK_CONSTANT_SYN_1, MOCK_PROC_SYN_1, MOCK_VAR_SYN_1,
         MOCK_PRINT_SYN_1},
        {MOCK_CONSTANT_SYN_2, MOCK_PROC_SYN_2, MOCK_VAR_SYN_2,
         MOCK_PRINT_SYN_2},
        {MOCK_CONSTANT_SYN_3, MOCK_PROC_SYN_3, MOCK_VAR_SYN_3,
         MOCK_PRINT_SYN_4},
        {MOCK_CONSTANT_SYN_4, MOCK_PROC_SYN_4, MOCK_VAR_SYN_4,
         MOCK_PRINT_SYN_3},
};

inline vector<vector<std::reference_wrapper<SynonymRes>>>
    DOUBLE_COL_SYNONYM_RES_DATA_CROSS = {
        {MOCK_DEFAULT_SYN_1, MOCK_CALLS_SYN_1, MOCK_CONSTANT_SYN_1,
         MOCK_PRINT_SYN_1},
        {MOCK_DEFAULT_SYN_1, MOCK_CALLS_SYN_1, MOCK_CONSTANT_SYN_2,
         MOCK_PRINT_SYN_2},
        {MOCK_DEFAULT_SYN_1, MOCK_CALLS_SYN_1, MOCK_CONSTANT_SYN_3,
         MOCK_PRINT_SYN_3},
        {MOCK_DEFAULT_SYN_1, MOCK_CALLS_SYN_1, MOCK_CONSTANT_SYN_4,
         MOCK_PRINT_SYN_4},
        {MOCK_DEFAULT_SYN_2, MOCK_CALLS_SYN_2, MOCK_CONSTANT_SYN_1,
         MOCK_PRINT_SYN_1},
        {MOCK_DEFAULT_SYN_2, MOCK_CALLS_SYN_2, MOCK_CONSTANT_SYN_2,
         MOCK_PRINT_SYN_2},
        {MOCK_DEFAULT_SYN_2, MOCK_CALLS_SYN_2, MOCK_CONSTANT_SYN_3,
         MOCK_PRINT_SYN_3},
        {MOCK_DEFAULT_SYN_2, MOCK_CALLS_SYN_2, MOCK_CONSTANT_SYN_4,
         MOCK_PRINT_SYN_4},
        {MOCK_DEFAULT_SYN_3, MOCK_CALLS_SYN_3, MOCK_CONSTANT_SYN_1,
         MOCK_PRINT_SYN_1},
        {MOCK_DEFAULT_SYN_3, MOCK_CALLS_SYN_3, MOCK_CONSTANT_SYN_2,
         MOCK_PRINT_SYN_2},
        {MOCK_DEFAULT_SYN_3, MOCK_CALLS_SYN_3, MOCK_CONSTANT_SYN_3,
         MOCK_PRINT_SYN_3},
        {MOCK_DEFAULT_SYN_3, MOCK_CALLS_SYN_3, MOCK_CONSTANT_SYN_4,
         MOCK_PRINT_SYN_4},
        {MOCK_DEFAULT_SYN_4, MOCK_CALLS_SYN_4, MOCK_CONSTANT_SYN_1,
         MOCK_PRINT_SYN_1},
        {MOCK_DEFAULT_SYN_4, MOCK_CALLS_SYN_4, MOCK_CONSTANT_SYN_2,
         MOCK_PRINT_SYN_2},
        {MOCK_DEFAULT_SYN_4, MOCK_CALLS_SYN_4, MOCK_CONSTANT_SYN_3,
         MOCK_PRINT_SYN_3},
        {MOCK_DEFAULT_SYN_4, MOCK_CALLS_SYN_4, MOCK_CONSTANT_SYN_4,
         MOCK_PRINT_SYN_4},
};

inline vector<vector<std::reference_wrapper<SynonymRes>>>
    MULTI_COL_SYNONYM_RES_DATA_INNER_JOIN = {
        {MOCK_DEFAULT_SYN_1, MOCK_CALLS_SYN_1, MOCK_STMT_SYN_1,
         MOCK_CONSTANT_SYN_1, MOCK_PROC_SYN_1, MOCK_VAR_SYN_1,
         MOCK_PRINT_SYN_1},
        {MOCK_DEFAULT_SYN_2, MOCK_CALLS_SYN_2, MOCK_STMT_SYN_2,
         MOCK_CONSTANT_SYN_2, MOCK_PROC_SYN_2, MOCK_VAR_SYN_2,
         MOCK_PRINT_SYN_2},
};
