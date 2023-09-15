#pragma once

#include <unordered_map>

using std::unordered_map;

enum PQLTokenType {
    SKIP_TOKEN, // " ", "\n", ";"

};

unordered_map<PQLTokenType, int> characters = {

};
