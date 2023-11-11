#include "IntermediateTableTestUtils.h"

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
      return false;
    }
  }
  return true;
}

TableDataType convertToSynonymResCol(const vector<string>& stringData) {
  TableDataType res {};
  res.reserve(stringData.size());
  for (const auto& stringDatum : stringData) {
    vector<std::reference_wrapper<SynonymRes>> datum = {
        SynonymResFactory::buildDefaultSynonym(stringDatum)};
    res.emplace_back(datum);
  }
  return res;
}

TableDataType convertToSynonymResCol(const vector<vector<string>>& stringData) {
  TableDataType res {};
  res.reserve(stringData.size());
  for (const auto& datumRow : stringData) {
    vector<std::reference_wrapper<SynonymRes>> row {};
    for (const auto& datum : datumRow) {
      row.emplace_back(SynonymResFactory::buildDefaultSynonym(datum));
    }
    res.emplace_back(row);
  }
  return res;
}

bool isTableDataSame(TableDataType data1, TableDataType data2) {
  if (data1.empty() && data2.empty()) {
    return true;
  }
  if (data1.size() != data2.size()) {
    return false;
  }
  if (data1.at(0).size() != data2.at(0).size()) {
    return false;
  }
  for (size_t i = 0; i < data1.size(); i++) {
    for (size_t j = 0; j < data1.at(i).size(); j++) {
      if (data1.at(i).at(j).get() != data2.at(i).at(j)) {
        return false;
      }
    }
  }
  return true;
}
