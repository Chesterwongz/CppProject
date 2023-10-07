#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "../../unit_testing/src/qps/testUtils/argumentFactory/ArgumentFactory.h"
#include "common/utils/StringUtils.h"
#include "qps/argument/AbstractArgument.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline vector<pair<string, string>> MOCK_NEXT_PAIRS({{"next 1", "next 2"},
                                                     {"next 3", "next 4"},
                                                     {"next 5", "next 6"},
                                                     {"next 7", "next 8"}});

inline vector<vector<string>> MOCK_NEXT_VECTORS({{"next 1", "next 2"},
                                                 {"next 3", "next 4"},
                                                 {"next 5", "next 6"},
                                                 {"next 7", "next 8"}});

inline vector<vector<string>> MOCK_NEXT_COL_1(
    {{"next 1"}, {"next 3"}, {"next 5"}, {"next 7"}});

inline vector<vector<string>> MOCK_NEXT_COL_2(
    {{"next 2"}, {"next 4"}, {"next 6"}, {"next 8"}});

inline vector<string> MOCK_NEXT_FIRST_STMTS = {
    "next first stmt1",
    "next first stmt2",
    "next first stmt3",
};
inline vector<vector<string>> MOCK_NEXT_FIRST_STMTS_2D = {
    {"next first stmt1"},
    {"next first stmt2"},
    {"next first stmt3"},
};

inline vector<string> MOCK_NEXT_SECOND_STMTS = {
    "next second stmt1",
    "next second stmt2",
    "next second stmt3",
};
inline vector<vector<string>> MOCK_NEXT_SECOND_STMTS_2D = {
    {"next second stmt1"},
    {"next second stmt2"},
    {"next second stmt3"},
};

inline vector<string> MOCK_NO_NEXT_STMTS = {};
