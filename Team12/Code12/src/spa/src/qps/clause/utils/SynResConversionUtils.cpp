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

bool SynResConversionUtils::isSynResCacheHit(const ClauseSignature& signature) {
  return SynResConversionUtils::synResCache.find(signature) !=
         SynResConversionUtils::synResCache.end();
}

bool SynResConversionUtils::isSingleColSynResCacheHit(
    const ClauseSignature& signature) {
  return SynResConversionUtils::singleColSynResCache.find(signature) !=
         SynResConversionUtils::singleColSynResCache.end();
}

void SynResConversionUtils::saveToSynResCache(
    const ClauseSignature& signature,
    const vector<vector<std::reference_wrapper<SynonymRes>>>& res) {
  // save copy to cache
  SynResConversionUtils::synResCache.insert(std::make_pair(signature, res));
}

void SynResConversionUtils::saveToSingleColSynResCache(
    const ClauseSignature& signature,
    const vector<std::reference_wrapper<SynonymRes>>& res) {
  // save copy to cache
  SynResConversionUtils::singleColSynResCache.insert(
      std::make_pair(signature, res));
}

vector<vector<std::reference_wrapper<SynonymRes>>>
SynResConversionUtils::getFromSynResCache(const ClauseSignature& signature) {
  return SynResConversionUtils::synResCache.at(signature);
}

vector<std::reference_wrapper<SynonymRes>>
SynResConversionUtils::getFromSingleColSynResCache(
    const ClauseSignature& signature) {
  // save copy to cache
  return SynResConversionUtils::singleColSynResCache.at(signature);
}

void SynResConversionUtils::clearSynResCache() {
  SynResConversionUtils::singleColSynResCache.clear();
  SynResConversionUtils::synResCache.clear();
}
