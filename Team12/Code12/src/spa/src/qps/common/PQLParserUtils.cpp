#include "PQLParserUtils.h"

PQLTokenType PQLParserUtils::getTokenTypeFromKeyword(const string &data) {
  auto entity = keywordToTokenType.find(data);

  if (entity != keywordToTokenType.end()) {
    return entity->second;
  } else {
    return PQL_NULL_TOKEN;
  }
}

bool PQLParserUtils::isValidAttrRefFromSynonym(const std::string &synonymType,
                                               const std::string &ref) {
  auto synRefPair = entityToAttrRef.find(synonymType);

  if (synRefPair == entityToAttrRef.end()) return false;

  auto availRef = synRefPair->second;
  return availRef.find(ref) != availRef.end();
}
