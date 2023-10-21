#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::vector;

class CollectionUtils {
 private:
  CollectionUtils() = default;

 public:
  template <typename T>
  static vector<T> intersectVectors(vector<T> vector1, vector<T> vector2) {
    std::sort(vector1.begin(), vector1.end());
    std::sort(vector2.begin(), vector2.end());

    vector<T> vectorIntersection;

    std::set_intersection(vector1.begin(), vector1.end(), vector2.begin(),
                          vector2.end(),
                          std::back_inserter(vectorIntersection));

    return vectorIntersection;
  }

  template <typename U, typename V>
  static std::vector<V> transformSetUToVectorV(
      const std::unordered_set<U>& setU, const std::function<V(U)>& mapper) {
    std::vector<V> res;
    res.reserve(setU.size());
    for (const U& u : setU) {
      res.push_back(mapper(u));
    }
    return res;
  }

  template <typename U, typename V>
  static std::vector<V> transformSetUToVectorV(
      const std::unordered_set<U>& setU, const std::function<V(U)>& mapper,
      const std::function<bool(U)>& filter) {
    std::vector<V> res;
    res.reserve(setU.size());
    for (const U& u : setU) {
      if (!filter(u)) continue;
      res.push_back(mapper(u));
    }
    return res;
  }

  static std::vector<std::string> intSetToStrVector(
      const std::unordered_set<int>& intSet,
      const std::function<bool(int)>& filter) {
    std::vector<std::string> res;
    res.reserve(res.size() + intSet.size());
    for (const int& val : intSet) {
      if (!filter(val)) continue;
      res.push_back(intToStrMapper(val));
    }
    return res;
  }

  static std::vector<std::pair<std::string, std::string>>
  intIntMapSetToStrPairVector(
      const std::unordered_map<int, std::unordered_set<int>>& mapSet,
      const std::pair<std::function<bool(int)>, std::function<bool(int)>>&
          filterPair) {
    std::vector<std::pair<std::string, std::string>> res;
    for (const auto& [a, setB] : mapSet) {
      if (!filterPair.first(a)) continue;
      for (const auto& b : setB) {
        if (!filterPair.second(b)) continue;
        res.emplace_back(intToStrMapper(a), intToStrMapper(b));
      }
    }
    return res;
  }

  static std::vector<std::pair<std::string, std::string>>
  intStrMapSetToStrPairVector(
      const std::unordered_map<int, std::unordered_set<std::string>>&
      mapSetAB) {
    std::vector<std::pair<std::string, std::string>> res;
    for (const auto& [a, setB] : mapSetAB) {
      res.reserve(res.size() + setB.size());
      for (const auto& b : setB) {
        res.emplace_back(intToStrMapper(a), b);
      }
    }
    return res;
  }

  static std::vector<std::pair<std::string, std::string>>
  intStrMapSetToStrPairVector(
      const std::unordered_map<int, std::unordered_set<std::string>>& mapSetAB,
      const std::function<bool(int)>& filter1) {
    std::vector<std::pair<std::string, std::string>> res;
    for (const auto& [a, setB] : mapSetAB) {
      if (!filter1(a)) continue;
      res.reserve(res.size() + setB.size());
      for (const auto& b : setB) {
        res.emplace_back(intToStrMapper(a), b);
      }
    }
    return res;
  }

  template <typename A, typename B>
  static std::vector<std::pair<A, B>> mapSetToPairVector(
      const std::unordered_map<A, std::unordered_set<B>>& mapSetAB) {
    std::vector<std::pair<A, B>> res;
    for (const auto& [a, setB] : mapSetAB) {
      res.reserve(res.size() + setB.size());
      for (const auto& b : setB) {
        res.emplace_back(a, b);
      }
    }
    return res;
  }

  static std::string intToStrMapper(const int& val) {
    return std::to_string(val);
  }
};
