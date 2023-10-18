#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/utils/StringUtils.h"
#include "qps/argument/AbstractArgument.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline vector<string> MOCK_MODIFYING_STATEMENTS({"modifying 1", "modifying 2",
                                                 "modifying 3"});

inline vector<string> MOCK_MODIFYING_PROCEDURES({"modifying 1", "modifying 2",
                                                 "modifying 3"});

inline vector<vector<string>> MOCK_MODIFYING_COL({{"modifying 1"},
                                                  {"modifying 2"},
                                                  {"modifying 3"}});

inline vector<pair<string, string>> MOCK_MODIFIED_PAIRS(
    {{"modifying 1", "modifying 2"},
     {"modifying 3", "modifying 4"},
     {"modifying 5", "modifying 6"},
     {"modifying 7", "modifying 8"}});

inline vector<vector<string>> MOCK_MODIFIED_VECTORS(
    {{"modifying 1", "modifying 2"},
     {"modifying 3", "modifying 4"},
     {"modifying 5", "modifying 6"},
     {"modifying 7", "modifying 8"}});

inline vector<vector<string>> MOCK_MODIFIED_VECTORS_COL_1(
    {{"modifying 1"}, {"modifying 3"}, {"modifying 5"}, {"modifying 7"}});

inline vector<vector<string>> MOCK_MODIFIED_VECTORS_COL_2(
    {{"modifying 2"}, {"modifying 4"}, {"modifying 6"}, {"modifying 8"}});

inline vector<string> MOCK_MODIFIED_FOR_PROCS({"modified 1", "modified 2",
                                               "modified 3"});

inline vector<vector<string>> MOCK_MODIFIED_VECTOR_FOR_PROCS({{"modified 1"},
                                                              {"modified 2"},
                                                              {"modified 3"}});
