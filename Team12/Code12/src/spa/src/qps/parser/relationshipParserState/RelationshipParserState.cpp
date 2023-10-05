#include "RelationshipParserState.h"

#include "qps/common/PQLParserUtils.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

RelationshipParserState::RelationshipParserState(bool isInBracket)
    : isInBracket(isInBracket) {}

void RelationshipParserState::processNameToken(PQLToken &curr) {
  if (this->isInBracket) {
    curr.updateTokenType(PQL_SYNONYM_TOKEN);
    return;
  }
  curr.updateTokenType(
      PQLParserUtils::getTokenTypeFromKeyword(curr.getValue()));
}

void RelationshipParserState::checkSafeExit(size_t expectedArgs,
                                            size_t actualArgs) {
  if (isInBracket || expectedArgs != actualArgs) {
    throw QPSInvalidQueryException(QPS_INVALID_QUERY_MISSING_ARGUMENTS);
  }
}
