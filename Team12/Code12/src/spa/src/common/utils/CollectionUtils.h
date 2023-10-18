#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
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

  template <typename U>
  static vector<U> concatVectors(vector<U> vector1, vector<U> vector2) {
    vector<U> newVector;
    newVector.reserve(vector1.size() + vector2.size());
    std::copy(vector1.begin(), vector1.end(), std::back_inserter(newVector));
    std::copy(vector2.begin(), vector2.end(), std::back_inserter(newVector));
    return newVector;
  }

  static vector<std::string> transformIntToStrVector(vector<int> toTransform) {
    std::vector<std::string> res;
    res.reserve(toTransform.size());
    std::transform(toTransform.begin(), toTransform.end(),
                   std::back_inserter(res),
                   [](const int& x) { return std::to_string(x); });
    return res;
  }

  static vector<std::pair<std::string, std::string>>
  transformIntIntToStrStrVector(vector<std::pair<int, int>> toTransform) {
    std::vector<std::pair<std::string, std::string>> res;
    res.reserve(toTransform.size());
    std::transform(toTransform.begin(), toTransform.end(),
                   std::back_inserter(res),
                   [](const std::pair<int, int>& intPair) {
                     return std::make_pair(std::to_string(intPair.first),
                                           std::to_string(intPair.second));
                   });
    return res;
  }

  static vector<std::pair<std::string, std::string>>
  transformIntStrToStrStrVector(
      vector<std::pair<int, std::string>> toTransform) {
    std::vector<std::pair<std::string, std::string>> res;
    res.reserve(toTransform.size());
    std::transform(toTransform.begin(), toTransform.end(),
                   std::back_inserter(res),
                   [](const std::pair<int, std::string>& intStrPair) {
                     return std::make_pair(std::to_string(intStrPair.first),
                                           intStrPair.second);
                   });
    return res;
  }

  template <typename U, typename V>
  static std::vector<V> transformSetUToVectorV(
      const std::unordered_set<U>& setU, std::function<V(U)> mapper,
      std::function<bool(U)> filter = [](const U&) { return true; }) {
    std::vector<V> res;
    res.reserve(setU.size());
    for (const U& u : setU) {
      if (!filter(u)) continue;
      res.push_back(mapper(u));
    }
    return res;
  }

  template <typename A, typename B, typename U = A, typename V = B>
  static std::vector<std::pair<U, V>> transformMapSetABToVectorUV(
      const std::unordered_map<A, std::unordered_set<B>>& mapSetAB,
      std::pair<std::function<U(A)>, std::function<V(B)>> mapperPair,
      std::pair<std::function<bool(A)>, std::function<bool(B)>> filterPair) {
    std::vector<std::pair<U, V>> res;
    for (const auto& [a, setB] : mapSetAB) {
      if (!filterPair.first(a)) continue;
      for (const auto& b : setB) {
        if (!filterPair.second(b)) continue;
        res.emplace_back(mapperPair.first(a), mapperPair.second(b));
      }
    }
    return res;
  }

  template <typename A, typename B, typename U = A, typename V = B>
  static std::vector<std::pair<U, V>> transformMapSetABToVectorUV(
      const std::unordered_map<A, std::unordered_set<B>>& mapSetAB,
      std::function<U(A)> mapper1, std::function<V(B)> mapper2) {
    std::vector<std::pair<U, V>> res;
    for (const auto& [a, setB] : mapSetAB) {
      res.reserve(setB.size());
      for (const auto& b : setB) {
        res.emplace_back(mapper1(a), mapper2(b));
      }
    }
    return res;
  }

  template <typename A, typename B, typename U = A>
  static std::vector<std::pair<U, B>> transformMapSetABToVectorUB(
      const std::unordered_map<A, std::unordered_set<B>>& mapSetAB,
      std::function<U(A)> mapper1, std::function<bool(A)> filter1) {
    std::vector<std::pair<U, B>> res;
    for (const auto& [a, setB] : mapSetAB) {
      if (!filter1(a)) continue;
      res.reserve(setB.size());
      for (const auto& b : setB) {
        res.emplace_back(mapper1(a), b);
      }
    }
    return res;
  }

  template <typename A, typename B, typename U = A>
  static std::vector<std::pair<U, B>> transformMapSetABToVectorUB(
      const std::unordered_map<A, std::unordered_set<B>>& mapSetAB,
      std::function<U(A)> mapper1) {
    std::vector<std::pair<U, B>> res;
    for (const auto& [a, setB] : mapSetAB) {
      res.reserve(setB.size());
      for (const auto& b : setB) {
        res.emplace_back(mapper1(a), b);
      }
    }
    return res;
  }

  template <typename A, typename B>
  static std::vector<std::pair<A, B>> transformMapSetABToVectorAB(
      const std::unordered_map<A, std::unordered_set<B>>& mapSetAB) {
    std::vector<std::pair<A, B>> res;
    for (const auto& [a, setB] : mapSetAB) {
      res.reserve(setB.size());
      for (const auto& b : setB) {
        res.emplace_back(a, b);
      }
    }
    return res;
  }

  static std::string intToStrMapper(const int& val) {
    return std::to_string(val);
  }

  static std::pair<std::function<std::string(int)>,
                   std::function<std::string(int)>>
  getIntToStrMapperPair() {
    return std::make_pair(CollectionUtils::intToStrMapper,
                          CollectionUtils::intToStrMapper);
  }
};
