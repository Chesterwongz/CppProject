#pragma once

#include <vector>
#include <algorithm>
#include <iterator>

using std::vector;

template <typename T>
vector<T> intersectVectors(vector<T> vector1, vector<T> vector2) {
    std::sort(vector1.begin(), vector1.end());
    std::sort(vector2.begin(), vector2.end());

    vector<T> vectorIntersection;

    std::set_intersection(vector1.begin(), vector1.end(),
                          vector2.begin(), vector2.end(),
                          std::back_inserter(vectorIntersection));

    return vectorIntersection;
}

template <typename U>
vector<U> concatVectors(vector<U> vector1, vector<U> vector2) {
    vector<U> newVector;
    newVector.reserve(vector1.size() + vector2.size());
    std::copy(vector1.begin(), vector1.end(), std::back_inserter(newVector));
    std::copy(vector2.begin(), vector2.end(), std::back_inserter(newVector));
    return newVector;
}
