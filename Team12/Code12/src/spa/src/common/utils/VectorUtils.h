#pragma once

#include <algorithm>
#include <iterator>
#include <vector>

using std::vector;

template <typename T>
vector<T> intersectVectors(vector<T> vector1, vector<T> vector2) {
  std::sort(vector1.begin(), vector1.end());
  std::sort(vector2.begin(), vector2.end());

  vector<T> vectorIntersection;

  std::set_intersection(vector1.begin(), vector1.end(), vector2.begin(),
                        vector2.end(), std::back_inserter(vectorIntersection));

  return vectorIntersection;
}
