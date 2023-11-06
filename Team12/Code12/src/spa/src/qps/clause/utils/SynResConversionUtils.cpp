#include "SynResConversionUtils.h"

vector<std::reference_wrapper<SynonymRes>> SynResConversionUtils::toSynonymRes(
    const vector<string>& res, const Entity& argEntity, PKBReader& pkbReader) {
  vector<std::reference_wrapper<SynonymRes>> synResVector {};
  synResVector.reserve(res.size());

  for (const string& datum : res) {
    synResVector.emplace_back(
        SynResConversionUtils::EntityToFuncMap.at(argEntity)(datum, pkbReader));
  }

  return synResVector;
}

vector<vector<std::reference_wrapper<SynonymRes>>>
SynResConversionUtils::toSynonymRes(const vector<pair<string, string>>& res,
                                    const pair<Entity, Entity>& argPair,
                                    PKBReader& pkbReader) {
  auto& [arg1Entity, arg2Entity] = argPair;

  vector<vector<std::reference_wrapper<SynonymRes>>> synResVector {};
  synResVector.reserve(res.size());
  for (auto& [val1, val2] : res) {
    vector<std::reference_wrapper<SynonymRes>> row {
        SynResConversionUtils::EntityToFuncMap.at(arg1Entity)(val1, pkbReader),
        SynResConversionUtils::EntityToFuncMap.at(arg2Entity)(val2, pkbReader),
    };
    synResVector.emplace_back(std::move(row));
  }

  return synResVector;
}
