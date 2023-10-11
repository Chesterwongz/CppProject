#pragma once

#include <string>
#include <unordered_set>
#include <vector>

using std::string, std::vector, std::unordered_set;

unordered_set<std::pair<std::string, std::string>> convertStringVectorToUnorderedSet(
    const vector<std::pair<std::string, std::string>>& stringVector);
