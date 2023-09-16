#pragma once

#include "qps/intermediateTable/IntermediateTable.h"

string COL_NAME_1 = "column 1";
string COL_NAME_2 = "column 2";
string COL_NAME_3 = "column 3";
string COL_NAME_4 = "column 4";

vector<string> doubleColNameVector = {COL_NAME_1, COL_NAME_2};
vector<pair<string, string>> PAIR_DATA = {
        { "0", "1" },
        { "2", "3" },
        { "4", "5" },
        { "6", "7" },
        { "6", "5" },
        { "4", "3" },
        { "2", "1" },
};

vector<string> doubleColNameVector2 = {COL_NAME_3, COL_NAME_4};
vector<vector<string>> DOUBLE_COL_VECTOR_DATA = {
        { "0", "1" },
        { "2", "3" },
        { "4", "5" },
        { "6", "7" },
        { "6", "5" },
        { "4", "3" },
        { "2", "1" },
};

vector<vector<string>> DOUBLE_COL_VECTOR_DATA_2 = {
        { "banana", "cat" },
        { "lettuce", "pineapple" },
        { "pear", "dog" },
        { "meow", "woof" },
        { "carrot", "durian" },
        { "tomato", "cucumber" },
        { "hamster", "mouse" },
};

vector<vector<string>> MULTI_COL_VECTOR_DATA = {
        { "0", "1", "banana", "cat" },
        { "2", "3", "lettuce", "pineapple" },
        { "4", "5", "pear", "dog" },
        { "6", "7", "meow", "woof" },
        { "6", "5", "carrot", "durian" },
        { "4", "3", "tomato", "cucumber" },
        { "2", "1", "hamster", "mouse" },
};

vector<string> COL_1 = {"0", "2", "4", "6", "6", "4", "2"};
vector<string> COL_2 = {"1", "3", "5", "7", "5", "3", "1"};
vector<string> COL_3 = {"banana", "lettuce", "pear", "meow", "carrot", "tomato", "hamster"};
vector<string> COL_4 = {"cat", "pineapple", "dog", "woof", "durian", "cucumber", "mouse"};

vector<vector<string> >COL_1_2D = {
        { "0", },
        { "2", },
        { "4", },
        { "6", },
        { "6", },
        { "4", },
        { "2", },
};
vector<vector<string>> COL_2_2D = {
        { "1" },
        { "3" },
        { "5" },
        { "7" },
        { "5" },
        { "3" },
        { "1" },
};
vector<vector<string>> COL_3_2D = {
        {"banana"},
        {"lettuce"},
        {"pear"},
        {"meow"},
        {"carrot"},
        {"tomato"},
        {"hamster"},
};
vector<vector<string>> COL_4_2D = {
        {"cat"},
        {"pineapple"},
        {"dog"},
        {"woof"},
        {"durian"},
        {"cucumber"},
        {"mouse"},
};

