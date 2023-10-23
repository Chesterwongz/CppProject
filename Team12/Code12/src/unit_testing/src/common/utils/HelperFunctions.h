#pragma once

#include <string>
#include <unordered_set>
#include <vector>

using std::string, std::vector, std::unordered_set;

unordered_set<string> convertStringVectorToUnorderedSet(
    const vector<string>& stringVector);

template <typename T>
bool compareVectorContents(vector<T> a, vector<T> b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (T& item : a) {
    bool isSameCountInBoth = std::count(a.begin(), a.end(), item) ==
                             std::count(b.begin(), b.end(), item);
    if (!isSameCountInBoth) {
      return false;
    }
  }
  return true;
}
