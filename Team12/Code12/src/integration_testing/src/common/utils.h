#pragma once

#include <vector>

using std::vector;

template <typename T>
inline bool compareVectorContents(vector<T> a, vector<T> b) {
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
