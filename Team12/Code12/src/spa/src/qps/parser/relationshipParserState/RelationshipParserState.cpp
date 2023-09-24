#include "RelationshipParserState.h"
#include "qps/common/PQLParserUtils.h"

RelationshipParserState::RelationshipParserState(bool isInBracket) : isInBracket(isInBracket) {}

void RelationshipParserState::processNameToken(PQLToken &curr) {
    if (this->isInBracket) {
        curr.updateTokenType(PQL_SYNONYM_TOKEN);
        return;
    }
    curr.updateTokenType(PQLParserUtils::getTokenTypeFromKeyword(curr.getValue()));
}

bool RelationshipParserState::isSafeExit(size_t expectedArgs, size_t actualArgs) {
    return !isInBracket && expectedArgs == actualArgs;
}
