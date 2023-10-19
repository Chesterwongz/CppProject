#include "IntermediateTableTestUtils.h"

#include <iostream>

bool isVectorSameAsPair(vector<string> vector1,
                        const pair<string, string>& pair1) {
  if (vector1.size() != 2) {
    return false;
  }
  return vector1.at(0) == pair1.first && vector1.at(1) == pair1.second;
}

bool isVectorsSameAsPairs(vector<vector<string>> vectors,
                          vector<pair<string, string>> pairs) {
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

vector<vector<SynonymRes>> convertToSynonymResCol(
    const vector<string>& stringData) {
  vector<vector<SynonymRes>> res{};
  res.reserve(stringData.size());
  for (const auto& stringDatum : stringData) {
    vector<SynonymRes> datum = {
        SynonymResFactory::buildDefaultSynonym(stringDatum)};
    res.emplace_back(datum);
  }
  return res;
}

vector<vector<SynonymRes>> convertToSynonymResCol(
    const vector<vector<string>>& stringData) {
  vector<vector<SynonymRes>> res{};
  res.reserve(stringData.size());
  for (const auto& datumRow : stringData) {
    vector<SynonymRes> row {};
    for (const auto& datum : datumRow) {
      row.emplace_back(SynonymResFactory::buildDefaultSynonym(datum));
    }
    res.emplace_back(row);
  }
  return res;
}
