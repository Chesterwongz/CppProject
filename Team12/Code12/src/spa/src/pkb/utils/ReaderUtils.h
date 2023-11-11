#pragma once

#include <string>
#include <unordered_set>
#include <vector>

class ReaderUtils {
 public:
  template <class T>
  static std::vector<std::string> readStrStore(
      bool shouldReturnEmpty, const std::unordered_set<T>& rawRes) {
    if (shouldReturnEmpty) {
      return {};
    }
    return {rawRes.begin(), rawRes.end()};
  }
};
