#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/utils/StringUtils.h"
#include "qps/argument/AbstractArgument.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline vector<pair<string, string>> MOCK_AFFECTS_PAIRS(
    {{"affects 1", "affects 2"},
     {"affects 3", "affects 4"},
     {"affects 5", "affects 6"},
     {"affects 7", "affects 8"}});

inline vector<vector<string>> MOCK_AFFECTS_VECTORS({{"affects 1", "affects 2"},
                                                    {"affects 3", "affects 4"},
                                                    {"affects 5", "affects 6"},
                                                    {"affects 7",
                                                     "affects 8"}});

inline vector<vector<string>> MOCK_AFFECTS_COL_1(
    {{"affects 1"}, {"affects 3"}, {"affects 5"}, {"affects 7"}});

inline vector<vector<string>> MOCK_AFFECTS_COL_2(
    {{"affects 2"}, {"affects 4"}, {"affects 6"}, {"affects 8"}});

inline vector<string> MOCK_AFFECTS = {
    "affects 1",
    "affects 2",
    "affects 3",
    "affects 4",
};
inline vector<vector<string>> MOCK_AFFECTS_COL = {
    {"affects 1"},
    {"affects 2"},
    {"affects 3"},
    {"affects 4"},
};

inline vector<string> MOCK_AFFECTED_BY = {
    "affected by 1",
    "affected by 2",
    "affected by 3",
    "affected by 4",
};
inline vector<vector<string>> MOCK_AFFECTED_BY_COL = {
    {"affected by 1"},
    {"affected by 2"},
    {"affected by 3"},
    {"affected by 4"},
};
