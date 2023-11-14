#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "qps/common/Keywords.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"

using std::string, std::pair, std::vector, std::set;

inline string COL_NAME_1 = "column 1";
inline string COL_NAME_2 = "column 2";
inline string COL_NAME_3 = "column 3";
inline string COL_NAME_4 = "column 4";
inline string COL_NAME_5 = "column 5";
inline string COL_NAME_6 = "column 6";
inline string COL_NAME_WILDCARD = WILDCARD_KEYWORD;

inline vector<string> DOUBLE_COL_NAME_VECTOR = {COL_NAME_1, COL_NAME_2};
inline vector<pair<string, string>> PAIR_DATA = {
    {"0", "1"}, {"2", "3"}, {"4", "5"}, {"6", "7"},
    {"6", "5"}, {"4", "3"}, {"2", "1"},
};

inline vector<string> doubleColNameVector2 = {COL_NAME_3, COL_NAME_4};
inline vector<vector<string>> DOUBLE_COL_VECTOR_DATA = {
    {"0", "1"}, {"2", "3"}, {"4", "5"}, {"6", "7"},
    {"6", "5"}, {"4", "3"}, {"2", "1"},
};

inline vector<vector<string>> DOUBLE_COL_VECTOR_DATA_2 = {
    {"banana", "cat"},    {"lettuce", "pineapple"}, {"pear", "dog"},
    {"meow", "woof"},     {"carrot", "durian"},     {"tomato", "cucumber"},
    {"hamster", "mouse"},
};

inline vector<vector<string>> DOUBLE_COL_VECTOR_DATA_CROSS = {
    {
        "0",
        "1",
        "banana",
        "cat",
    },
    {
        "0",
        "1",
        "lettuce",
        "pineapple",
    },
    {
        "0",
        "1",
        "pear",
        "dog",
    },
    {
        "0",
        "1",
        "meow",
        "woof",
    },
    {
        "0",
        "1",
        "carrot",
        "durian",
    },
    {
        "0",
        "1",
        "tomato",
        "cucumber",
    },
    {
        "0",
        "1",
        "hamster",
        "mouse",
    },
    {
        "2",
        "3",
        "banana",
        "cat",
    },
    {
        "2",
        "3",
        "lettuce",
        "pineapple",
    },
    {
        "2",
        "3",
        "pear",
        "dog",
    },
    {
        "2",
        "3",
        "meow",
        "woof",
    },
    {
        "2",
        "3",
        "carrot",
        "durian",
    },
    {
        "2",
        "3",
        "tomato",
        "cucumber",
    },
    {
        "2",
        "3",
        "hamster",
        "mouse",
    },
    {
        "4",
        "5",
        "banana",
        "cat",
    },
    {
        "4",
        "5",
        "lettuce",
        "pineapple",
    },
    {
        "4",
        "5",
        "pear",
        "dog",
    },
    {
        "4",
        "5",
        "meow",
        "woof",
    },
    {
        "4",
        "5",
        "carrot",
        "durian",
    },
    {
        "4",
        "5",
        "tomato",
        "cucumber",
    },
    {
        "4",
        "5",
        "hamster",
        "mouse",
    },
    {
        "6",
        "7",
        "banana",
        "cat",
    },
    {
        "6",
        "7",
        "lettuce",
        "pineapple",
    },
    {
        "6",
        "7",
        "pear",
        "dog",
    },
    {
        "6",
        "7",
        "meow",
        "woof",
    },
    {
        "6",
        "7",
        "carrot",
        "durian",
    },
    {
        "6",
        "7",
        "tomato",
        "cucumber",
    },
    {
        "6",
        "7",
        "hamster",
        "mouse",
    },
    {
        "6",
        "5",
        "banana",
        "cat",
    },
    {
        "6",
        "5",
        "lettuce",
        "pineapple",
    },
    {
        "6",
        "5",
        "pear",
        "dog",
    },
    {
        "6",
        "5",
        "meow",
        "woof",
    },
    {
        "6",
        "5",
        "carrot",
        "durian",
    },
    {
        "6",
        "5",
        "tomato",
        "cucumber",
    },
    {
        "6",
        "5",
        "hamster",
        "mouse",
    },
    {
        "4",
        "3",
        "banana",
        "cat",
    },
    {
        "4",
        "3",
        "lettuce",
        "pineapple",
    },
    {
        "4",
        "3",
        "pear",
        "dog",
    },
    {
        "4",
        "3",
        "meow",
        "woof",
    },
    {
        "4",
        "3",
        "carrot",
        "durian",
    },
    {
        "4",
        "3",
        "tomato",
        "cucumber",
    },
    {
        "4",
        "3",
        "hamster",
        "mouse",
    },
    {
        "2",
        "1",
        "banana",
        "cat",
    },
    {
        "2",
        "1",
        "lettuce",
        "pineapple",
    },
    {
        "2",
        "1",
        "pear",
        "dog",
    },
    {
        "2",
        "1",
        "meow",
        "woof",
    },
    {
        "2",
        "1",
        "carrot",
        "durian",
    },
    {
        "2",
        "1",
        "tomato",
        "cucumber",
    },
    {
        "2",
        "1",
        "hamster",
        "mouse",
    },
};

inline vector<string> MULTI_COL_NAME_VECTOR_1 = {COL_NAME_4, COL_NAME_3,
                                                 COL_NAME_2, COL_NAME_1};
inline vector<string> MULTI_COL_NAME_VECTOR_WITH_WILDCARD = {
    COL_NAME_4, COL_NAME_3, COL_NAME_WILDCARD, COL_NAME_1};
inline vector<vector<string>> MULTI_COL_DATA_1 = {
    {"0", "1", "banana", "cat"},    {"2", "3", "lettuce", "pineapple"},
    {"4", "5", "pear", "dog"},      {"6", "7", "meow", "woof"},
    {"6", "5", "carrot", "durian"}, {"4", "3", "tomato", "cucumber"},
    {"2", "1", "hamster", "mouse"},
};
inline vector<vector<string>> MULTI_COL_DATA_1_WILDCARD = {
    {"0", "1", "cat"},   {"2", "3", "pineapple"}, {"4", "5", "dog"},
    {"6", "7", "woof"},  {"6", "5", "durian"},    {"4", "3", "cucumber"},
    {"2", "1", "mouse"},
};

inline vector<string> MULTI_COL_NAME_VECTOR_2 = {COL_NAME_5, COL_NAME_6,
                                                 COL_NAME_2, COL_NAME_1};
inline vector<vector<string>> MULTI_COL_DATA_2 = {
    {"0", "1", "banana", "cat"},
    {"2", "3", "lettuce", "lettuce"},
    {"banana", "cat", "carrot", "durian"},
    {"4", "3", "hamster", "mouse"},
    {"4", "5", "dog", "dog"},
    {"6", "7", "woof", "meow"},
};

inline vector<vector<string>> MULTI_COL_DATA_JOIN = {
    {"0", "1", "banana", "cat", "0", "1"},
    {"6", "5", "carrot", "durian", "banana", "cat"},
    {"2", "1", "hamster", "mouse", "4", "3"}};

inline string COL_SINGLETON = "cat";

inline vector<vector<string>> COL_1_2D = {
    {
        "0",
    },
    {
        "2",
    },
    {
        "4",
    },
    {
        "6",
    },
    {
        "6",
    },
    {
        "4",
    },
    {
        "2",
    },
};
inline vector<vector<string>> COL_2_2D = {
    {"1"}, {"3"}, {"5"}, {"7"}, {"5"}, {"3"}, {"1"},
};
inline vector<vector<string>> COL_SINGLETON_2D = {
    {"cat"},
};

inline IntermediateTable WILDCARD_TABLE =
    IntermediateTableFactory::buildWildcardIntermediateTable();

inline IntermediateTable EMPTY_TABLE =
    IntermediateTableFactory::buildEmptyIntermediateTable();
