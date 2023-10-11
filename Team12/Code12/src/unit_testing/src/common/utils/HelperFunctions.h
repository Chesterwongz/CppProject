#pragma once

#include <string>
#include <unordered_set>
#include <vector>

using std::string, std::vector, std::unordered_set;

unordered_set<string> convertStringVectorToUnorderedSet(
    const vector<string>& stringVector);

unordered_set<std::pair<std::string, std::string>> convertStringVectorPairToUnorderedSet(
    const vector<std::pair<std::string, std::string>>& stringVector);
