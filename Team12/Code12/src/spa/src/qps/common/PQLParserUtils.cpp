#include "PQLParserUtils.h"

PQLTokenType PQLParserUtils::getTokenTypeFromKeyword(const string &data) {
    auto entity = keywordToTokenType.find(data);

    if (entity != keywordToTokenType.end()) {
        return entity->second;
    } else {
        return PQL_NULL_TOKEN;
    }
}

bool PQLParserUtils::isExpectedToken(PredictiveMap &pm, PQLTokenType prev, PQLTokenType curr) {
    auto nextTokens = pm.find(prev);

    if (nextTokens == pm.end()) {
        return false;
    }
    auto nextSteps = nextTokens->second;
    if (nextSteps.find(curr) == nextSteps.end()) {
        return false;
    }
    return true;
}

bool PQLParserUtils::isDelimiter(PQLTokenType tokenType) {
    return delimiterTokens.find(tokenType) != delimiterTokens.end();
}

void PQLParserUtils::processNameTokenInRelationships(PQLToken &curr, bool isInBracket) {
    if (isInBracket) {
        curr.updateTokenType(PQL_SYNONYM_TOKEN);
        return;
    }
    curr.updateTokenType(PQLParserUtils::getTokenTypeFromKeyword(curr.getValue()));
}
