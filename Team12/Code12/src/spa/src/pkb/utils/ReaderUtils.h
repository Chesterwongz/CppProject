#pragma once

#include <functional>
#include <string>
#include <unordered_set>
#include <vector>

class ReaderUtils {
 public:
  static std::vector<std::string> readStrStore(
      bool shouldReturnEmpty,
      const std::function<std::unordered_set<std::string>()>& resGetter) {
    if (shouldReturnEmpty) {
      return {};
    }
    const std::unordered_set<std::string>& rawRes = resGetter();
    return {rawRes.begin(), rawRes.end()};
  }
};
