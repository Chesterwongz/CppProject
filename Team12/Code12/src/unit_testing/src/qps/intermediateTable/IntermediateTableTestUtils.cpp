#include <iostream>
#include "IntermediateTableTestUtils.h"

bool isVectorSameAsPair(vector<string> vector1, const pair<string, string>& pair1) {
    if (vector1.size() != 2) {
        return false;
    }
    return vector1.at(0) == pair1.first && vector1.at(1) == pair1.second;
}

bool isVectorsSameAsPairs(vector<vector<string>> vectors, vector<pair<string, string>> pairs) {
    if (vectors.size() != pairs.size()) {
        return false;
    }
    for (int i = 0; i < vectors.size(); i++) {
        if (!isVectorSameAsPair(vectors.at(i), pairs.at(i))) {
            std::cout << "row " << i << " incorrect" << std::endl;
            return false;
        }
    }
    std::cout << "vectors matches pairs" << std::endl;
    return true;
}
