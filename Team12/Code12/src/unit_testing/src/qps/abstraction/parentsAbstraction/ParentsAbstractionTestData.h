#pragma once

#include <set>
#include <vector>
#include <memory>
#include "qps/argument/AbstractArgument.h"
#include "common/utils/StringUtils.h"
#include "../../testUtils/argumentFactory/ArgumentFactory.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline pair<string, string> MOCK_IMMEDIATE_PARENT_OF = {"98", "99"};

inline pair<string, string> MOCK_INVALID_IMMEDIATE_PARENT = {"", ""};

inline vector<pair<string, string>>MOCK_PARENT_CHILD_PAIRS(
        {{"pc 1", "pc 2"},
         {"pc 3", "pc 4"},
         {"pc 5", "pc 6"},
         {"pc 7", "pc 8"}});

inline vector<vector<string>>MOCK_PARENT_CHILD_VECTORS(
        {{"pc 1", "pc 2"},
         {"pc 3", "pc 4"},
         {"pc 5", "pc 6"},
         {"pc 7", "pc 8"}});

inline vector<vector<string>>MOCK_PARENT_CHILD_COL_1(
        {{"pc 1"},
         {"pc 3"},
         {"pc 5"},
         {"pc 7"}});

inline vector<vector<string>>MOCK_PARENT_CHILD_COL_2(
        {{"pc 2"},
         {"pc 4"},
         {"pc 6"},
         {"pc 8"}});

inline vector<pair<string, string>>MOCK_PARENT_CHILD_STARS_PAIRS(
        {{"pc stars 1", "pc stars 2"},
         {"pc stars 3", "pc stars 4"},
         {"pc stars 5", "pc stars 6"},
         {"pc stars 7", "pc stars 8"}});

inline vector<vector<string>>MOCK_PARENT_CHILD_STARS_COL_2(
        {{"pc stars 2"},
         {"pc stars 4"},
         {"pc stars 6"},
         {"pc stars 8"}});
