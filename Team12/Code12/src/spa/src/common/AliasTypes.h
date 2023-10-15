#pragma once

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/utils/PairUtils.h"

using std::string, std::unordered_map, std::map, std::unordered_set, std::set,
    std::vector, std::pair;

using IntToIntSetMap = std::unordered_map<int, std::unordered_set<int>>;
using IntSet = std::unordered_set<int>;
using StrStrPairSet = unordered_set<pair<string, string>, PairUtils::PairHash>;
using StrStrPairVec = vector<pair<string, string>>;
using ProcToStrSetMap = unordered_map<string, unordered_set<string>>;
