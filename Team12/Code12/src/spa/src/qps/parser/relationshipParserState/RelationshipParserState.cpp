#include "RelationshipParserState.h"

#include <utility>

#include "qps/common/PQLParserUtils.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

RelationshipParserState::RelationshipParserState(
    PQLParserContext &parserContext, bool isInBracket, string abstraction,
    PQLTokenType prev)
    : isInBracket(isInBracket),
      abstraction(std::move(abstraction)),
      BaseParserState(parserContext, prev) {}

void RelationshipParserState::processNameToken(PQLToken &curr) {
  if (this->isInBracket) {
    if (QPSStringUtils::isSynonym(curr.getValue())) {
      curr.updateTokenType(PQL_SYNONYM_TOKEN);
    } else {
      curr.updateTokenType(PQL_NULL_TOKEN);
    }
    return;
  }
  curr.updateTokenType(
      PQLParserUtils::getTokenTypeFromKeyword(curr.getValue()));
}

unique_ptr<SuchThatClause> RelationshipParserState::createSuchThatClause(
    Abstraction abstractionEnum) {
  if (arguments.size() != expectedNumberOfArgs) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }

  return std::make_unique<SuchThatClause>(abstractionEnum,
                                          std::move(arguments.at(FIRST_ARG)),
                                          std::move(arguments.at(SECOND_ARG)));
}

Abstraction RelationshipParserState::getAbstractionType(
    const std::string &keyword,
    unordered_map<string, Abstraction> abstractionKeywordMap) {
  auto mapRes = abstractionKeywordMap.find(keyword);
  if (mapRes == abstractionKeywordMap.end()) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR + keyword);
  }
  return mapRes->second;
}
