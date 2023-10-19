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

namespace MOCK_CALLS_STAR_DATA {

inline vector<string> MOCK_CALLER_STAR_PROCS({"caller star 1", "caller star 2",
                                              "caller star 3"});
inline vector<vector<string>> MOCK_CALLER_STAR_PROCS_COL({{"caller star 1"},
                                                          {"caller star 2"},
                                                          {"caller star 3"}});
inline vector<string> MOCK_CALLEE_STAR_PROCS({"callee star 1", "callee star 2",
                                              "callee star 3"});
inline vector<vector<string>> MOCK_CALLEE_STAR_PROCS_COL({{"callee star 1"},
                                                          {"callee star 2"},
                                                          {"callee star 3"}});

inline vector<pair<string, string>> MOCK_CALL_STAR_PAIRS(
    {{"call star 1", "call star 2"},
     {"call star 3", "call star 4"},
     {"call star 5", "call star 6"},
     {"call star 7", "call star 8"}});

inline vector<vector<string>> MOCK_CALL_STAR_PAIRS_VECTORS(
    {{"call star 1", "call star 2"},
     {"call star 3", "call star 4"},
     {"call star 5", "call star 6"},
     {"call star 7", "call star 8"}});

inline vector<vector<string>> MOCK_CALLED_STAR_VECTORS_COL_1(
    {{"call star 1"}, {"call star 3"}, {"call star 5"}, {"call star 7"}});

inline vector<vector<string>> MOCK_CALLED_STAR_VECTORS_COL_2(
    {{"call star 2"}, {"call star 4"}, {"call star 6"}, {"call star 8"}});
}  // namespace MOCK_CALLS_STAR_DATA
