#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/utils/StringUtils.h"
#include "qps/argument/AbstractArgument.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline vector<pair<string, string>> MOCK_NEXT_STAR_PAIRS(
    {{"next star 1", "next star 2"},
     {"next star 3", "next star 4"},
     {"next star 5", "next star 6"},
     {"next star 7", "next star 8"}});

inline vector<vector<string>> MOCK_NEXT_STAR_VECTORS(
    {{"next star 1", "next star 2"},
     {"next star 3", "next star 4"},
     {"next star 5", "next star 6"},
     {"next star 7", "next star 8"}});

inline vector<vector<string>> MOCK_NEXT_STAR_COL_1(
    {{"next star 1"}, {"next star 3"}, {"next star 5"}, {"next star 7"}});

inline vector<vector<string>> MOCK_NEXT_STAR_COL_2(
    {{"next star 2"}, {"next star 4"}, {"next star 6"}, {"next star 8"}});

inline vector<string> MOCK_NEXT_STAR_FIRST_STMTS = {
    "next star first stmt1",
    "next star first stmt2",
    "next star first stmt3",
};
inline vector<vector<string>> MOCK_NEXT_STAR_FIRST_STMTS_2D = {
    {"next star first stmt1"},
    {"next star first stmt2"},
    {"next star first stmt3"},
};

inline vector<string> MOCK_NEXT_STAR_SECOND_STMTS = {
    "next star second stmt1",
    "next star second stmt2",
    "next star second stmt3",
};
inline vector<vector<string>> MOCK_NEXT_STAR_SECOND_STMTS_2D = {
    {"next star second stmt1"},
    {"next star second stmt2"},
    {"next star second stmt3"},
};

inline vector<string> MOCK_NO_NEXT_STAR_STMTS = {};
