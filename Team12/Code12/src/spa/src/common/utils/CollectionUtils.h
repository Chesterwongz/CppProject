#pragma once

#include <algorithm>
#include <iterator>
#include <string>
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
    std::transform(toTransform.begin(), toTransform.end(),
                   std::back_inserter(res),
                   [](int x) { return std::to_string(x); });
    return res;
  }

  static vector<std::pair<std::string, std::string>>
  transformIntIntToStrStrVector(vector<std::pair<int, int>> toTransform) {
    std::vector<std::pair<std::string, std::string>> res;
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
    std::transform(toTransform.begin(), toTransform.end(),
                   std::back_inserter(res),
                   [](const std::pair<int, std::string>& intStrPair) {
                     return std::make_pair(std::to_string(intStrPair.first),
                                           intStrPair.second);
                   });
    return res;
  }
};
