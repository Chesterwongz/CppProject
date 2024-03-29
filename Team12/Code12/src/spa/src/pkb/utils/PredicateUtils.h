#pragma once

#include <functional>
#include <unordered_set>

class PredicateUtils {
 private:
  PredicateUtils() = default;

 public:
  template <typename T>
  static std::function<bool(T)> isInSet(const std::unordered_set<T>& set) {
    return [set](const T& val) { return set.count(val); };
  }

  template <typename T>
  static std::function<bool(T)> returnTrue() {
    return [](const T& val) { return true; };
  }
};
