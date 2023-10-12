#pragma once

#include <string>
#include <unordered_set>
#include <vector>

using std::string, std::vector, std::unordered_set;

unordered_set<string> convertStringVectorToUnorderedSet(
    const vector<string>& stringVector);
