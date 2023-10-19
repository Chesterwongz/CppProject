#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "../../unit_testing/src/qps/testUtils/argumentFactory/ArgumentFactory.h"
#include "common/utils/StringUtils.h"
#include "qps/argument/AbstractArgument.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline vector<pair<string, string>> MOCK_FOLLOWS_STARS_PAIRS(
    {{"follows stars 1", "follows stars 2"},
     {"follows stars 3", "follows stars 4"},
     {"follows stars 5", "follows stars 6"},
     {"follows stars 7", "follows stars 8"}});

inline vector<vector<string>> MOCK_FOLLOWS_STARS_VECTOR(
    {{"follows stars 1", "follows stars 2"},
     {"follows stars 3", "follows stars 4"},
     {"follows stars 5", "follows stars 6"},
     {"follows stars 7", "follows stars 8"}});

inline vector<vector<string>> MOCK_FOLLOWED_STAR_COL_1({{"follows stars 1"},
                                                        {"follows stars 3"},
                                                        {"follows stars 5"},
                                                        {"follows stars 7"}});

inline vector<vector<string>> MOCK_FOLLOWS_STARS_COL_2({{"follows stars 2"},
                                                        {"follows stars 4"},
                                                        {"follows stars 6"},
                                                        {"follows stars 8"}});

inline vector<string> MOCK_FOLLOWS_STARS_1({"follows stars 1",
                                            "follows stars 3",
                                            "follows stars 5",
                                            "follows stars 7"});

inline vector<string> MOCK_FOLLOWS_STARS_2({"follows stars 2",
                                            "follows stars 4",
                                            "follows stars 6",
                                            "follows stars 8"});

inline string MOCK_FOLLOWED = "99";
inline string MOCK_NO_FOLLOWED = INVALID_STATEMENT_NUMBER;
inline vector<pair<string, string>> MOCK_FOLLOWED_STAR(
    {{"1", "follows stars 2"},
     {"1", "follows stars 4"},
     {"1", "follows stars 6"},
     {"1", "follows stars 8"}});
