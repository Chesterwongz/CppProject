#include "PQLParserUtils.h"

PQLTokenType PQLParserUtils::getTokenTypeFromKeyword(const string &data) {
  auto entity = keywordToTokenType.find(data);

  if (entity != keywordToTokenType.end()) {
    return entity->second;
  } else {
    return PQL_NULL_TOKEN;
  }
}
