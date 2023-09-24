#pragma once

#include <string>
#include <vector>
#include <unordered_set>

using std::string, std::vector, std::unordered_set;

unordered_set<string> convertStringVectorToUnorderedSet(const vector<string>& stringVector);

