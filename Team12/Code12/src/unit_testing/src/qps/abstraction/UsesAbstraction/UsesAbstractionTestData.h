#pragma once

#include <set>
#include <vector>
#include <memory>
#include "qps/argument/argumentFactory/ArgumentFactory.h"
#include "qps/argument/IArgument.h"
#include "common/utils/StringUtils.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline vector<string>MOCK_USING_STATEMENTS(
        {"using 1",
         "using 2",
         "using 3"});

inline vector<vector<string>>MOCK_USING_STATEMENTS_COL(
        {{"using 1"},
         {"using 2"},
         {"using 3"}});

inline vector<pair<string, string>>MOCK_USED_PAIRS(
        {{"using 1", "using 2"},
         {"using 3", "using 4"},
         {"using 5", "using 6"},
         {"using 7", "using 8"}});

inline vector<vector<string>>MOCK_USED_VECTORS(
        {{"using 1", "using 2"},
         {"using 3", "using 4"},
         {"using 5", "using 6"},
         {"using 7", "using 8"}});

inline vector<vector<string>>MOCK_USED_VECTORS_COL_1(
        {{"using 1"},
         {"using 3"},
         {"using 5"},
         {"using 7"}});

inline vector<vector<string>>MOCK_USED_VECTORS_COL_2(
        {{"using 2"},
         {"using 4"},
         {"using 6"},
         {"using 8"}});