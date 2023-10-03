#pragma once

#include <memory>
#include <set>
#include <vector>

#include "../../unit_testing/src/qps/testUtils/argumentFactory/ArgumentFactory.h"
#include "common/utils/StringUtils.h"
#include "qps/argument/AbstractArgument.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline vector<pair<string, string>> MOCK_FOLLOWS_PAIRS(
    {{"follows 1", "follows 2"},
     {"follows 3", "follows 4"},
     {"follows 5", "follows 6"},
     {"follows 7", "follows 8"}});

inline vector<vector<string>> MOCK_FOLLOWS_VECTORS({{"follows 1", "follows 2"},
                                                    {"follows 3", "follows 4"},
                                                    {"follows 5", "follows 6"},
                                                    {"follows 7",
                                                     "follows 8"}});

inline vector<vector<string>> MOCK_FOLLOWS_COL_1(
    {{"follows 1"}, {"follows 3"}, {"follows 5"}, {"follows 7"}});

inline vector<vector<string>> MOCK_FOLLOWS_COL_2(
    {{"follows 2"}, {"follows 4"}, {"follows 6"}, {"follows 8"}});

inline string MOCK_FOLLOWED = "99";
inline string MOCK_NO_FOLLOWED = INVALID_STATEMENT_NUMBER;
