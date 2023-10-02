#pragma once

#include <set>
#include <vector>
#include <memory>
#include "../../unit_testing/src/qps/testUtils/argumentFactory/ArgumentFactory.h"
#include "qps/argument/AbstractArgument.h"
#include "common/utils/StringUtils.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline pair<string, string> MOCK_IMMEDIATE_PARENT_OF = {"98", "99"};

inline pair<string, string> MOCK_INVALID_IMMEDIATE_PARENT = {"", ""};

inline vector<pair<string, string>>MOCK_PARENT_CHILD_STARS_PAIRS(
        {{"pc stars 1", "pc stars 2"},
         {"pc stars 3", "pc stars 4"},
         {"pc stars 5", "pc stars 6"},
         {"pc stars 7", "pc stars 8"}});

inline vector<vector<string>>MOCK_PARENT_CHILD_STARS_VECTOR(
        {{"pc stars 1", "pc stars 2"},
         {"pc stars 3", "pc stars 4"},
         {"pc stars 5", "pc stars 6"},
         {"pc stars 7", "pc stars 8"}});

inline vector<vector<string>>MOCK_PARENT_CHILD_STARS_COL_1(
        {{"pc stars 1"},
         {"pc stars 3"},
         {"pc stars 5"},
         {"pc stars 7"}});


inline vector<vector<string>>MOCK_PARENT_CHILD_STARS_COL_2(
        {{"pc stars 2"},
         {"pc stars 4"},
         {"pc stars 6"},
         {"pc stars 8"}});
