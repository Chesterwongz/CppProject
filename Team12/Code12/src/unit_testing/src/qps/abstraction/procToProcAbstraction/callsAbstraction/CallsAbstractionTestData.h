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

namespace MOCK_CALLS_DATA {

inline vector<string> MOCK_CALLER_PROCS({"caller 1", "caller 2", "caller 3"});
inline vector<vector<string>> MOCK_CALLER_PROCS_COL({{"caller 1"},
                                                     {"caller 2"},
                                                     {"caller 3"}});
inline vector<string> MOCK_CALLEE_PROCS({"callee 1", "callee 2", "callee 3"});
inline vector<vector<string>> MOCK_CALLEE_PROCS_COL({{"callee 1"},
                                                     {"callee 2"},
                                                     {"callee 3"}});

inline vector<pair<string, string>> MOCK_CALL_PAIRS({{"call 1", "call 2"},
                                                     {"call 3", "call 4"},
                                                     {"call 5", "call 6"},
                                                     {"call 7", "call 8"}});

inline vector<vector<string>> MOCK_CALL_PAIRS_VECTORS({{"call 1", "call 2"},
                                                       {"call 3", "call 4"},
                                                       {"call 5", "call 6"},
                                                       {"call 7", "call 8"}});

inline vector<vector<string>> MOCK_CALLED_VECTORS_COL_1(
    {{"call 1"}, {"call 3"}, {"call 5"}, {"call 7"}});

inline vector<vector<string>> MOCK_CALLED_VECTORS_COL_2(
    {{"call 2"}, {"call 4"}, {"call 6"}, {"call 8"}});
}  // namespace MOCK_CALLS_DATA
