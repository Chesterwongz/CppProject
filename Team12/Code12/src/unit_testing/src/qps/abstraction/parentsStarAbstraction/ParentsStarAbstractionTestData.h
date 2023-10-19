#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/utils/StringUtils.h"
#include "qps/argument/AbstractArgument.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline pair<string, string> MOCK_IMMEDIATE_PARENT_OF = {"98", "99"};

inline pair<string, string> MOCK_INVALID_IMMEDIATE_PARENT = {"", ""};

inline vector<pair<string, string>> MOCK_PARENT_CHILD_STARS_PAIRS(
    {{"pc stars 1", "pc stars 2"},
     {"pc stars 3", "pc stars 4"},
     {"pc stars 5", "pc stars 6"},
     {"pc stars 7", "pc stars 8"}});

inline vector<vector<string>> MOCK_PARENT_CHILD_STARS_VECTOR(
    {{"pc stars 1", "pc stars 2"},
     {"pc stars 3", "pc stars 4"},
     {"pc stars 5", "pc stars 6"},
     {"pc stars 7", "pc stars 8"}});

inline vector<string> MOCK_PARENT_STARS(
    {"pc stars 1", "pc stars 3", "pc stars 5", "pc stars 7"});

inline vector<string> MOCK_CHILD_STARS(
    {"pc stars 2", "pc stars 4", "pc stars 6", "pc stars 8"});

inline vector<vector<string>> MOCK_PARENT_CHILD_STARS_COL_1(
    {{"pc stars 1"}, {"pc stars 3"}, {"pc stars 5"}, {"pc stars 7"}});

inline vector<vector<string>> MOCK_PARENT_CHILD_STARS_COL_2(
    {{"pc stars 2"}, {"pc stars 4"}, {"pc stars 6"}, {"pc stars 8"}});
