#pragma once

#include <set>
#include <vector>
#include <memory>
#include "qps/argument/argumentFactory/ArgumentFactory.h"
#include "qps/argument/IArgument.h"
#include "common/utils/StringUtils.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline vector<pair<string, string>>MOCK_FOLLOWS_PAIRS(
        {{"follows 1", "follows 2"},
         {"follows 3", "follows 4"},
         {"follows 5", "follows 6"},
         {"follows 7", "follows 8"}});

inline vector<vector<string>>MOCK_FOLLOWS_VECTORS(
        {{"follows 1", "follows 2"},
         {"follows 3", "follows 4"},
         {"follows 5", "follows 6"},
         {"follows 7", "follows 8"}});

inline vector<vector<string>>MOCK_FOLLOWS_COL_1(
        {{"follows 1"},
         {"follows 3"},
         {"follows 5"},
         {"follows 7"}});

inline vector<vector<string>>MOCK_FOLLOWS_COL_2(
        {{"follows 2"},
         {"follows 4"},
         {"follows 6"},
         {"follows 8"}});

inline vector<pair<string, string>>MOCK_FOLLOWS_STARS_PAIRS(
        {{"follows stars 1", "follows stars 2"},
         {"follows stars 3", "follows stars 4"},
         {"follows stars 5", "follows stars 6"},
         {"follows stars 7", "follows stars 8"}});

inline vector<vector<string>>MOCK_FOLLOWS_STARS_COL_2(
        {{"follows stars 2"},
         {"follows stars 4"},
         {"follows stars 6"},
         {"follows stars 8"}});

inline string MOCK_FOLLOWED = "99";
inline string MOCK_NO_FOLLOWED = INVALID_STATEMENT_NUMBER;
inline vector<pair<string, string>>MOCK_FOLLOWED_STAR (
        {{"1", "follows stars 2"},
         {"1", "follows stars 4"},
         {"1", "follows stars 6"},
         {"1", "follows stars 8"}});

inline vector<vector<string>>MOCK_FOLLOWED_STAR_COL (
        {{"follows stars 2"},
         {"follows stars 4"},
         {"follows stars 6"},
         {"follows stars 8"}});
