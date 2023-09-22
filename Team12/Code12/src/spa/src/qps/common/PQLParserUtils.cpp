#include "PQLParserUtils.h"

bool PQLParserUtils::isValidName(string &data) {
	regex synonymPattern("^[A-Za-z][A-Za-z0-9]*$");
	return regex_match(data, synonymPattern);
}

bool PQLParserUtils::isValidInteger(string &data) {
	regex integerPattern("^[1-9][0-9]*$");
	return regex_match(data, integerPattern);
}

bool PQLParserUtils::isSynonym(string data) {
	return isValidName(data);
}

bool PQLParserUtils::isStmtRef(string data) {
	return isSynonym(data) || data == "_" || isValidInteger(data);
}

bool PQLParserUtils::isEntRef(string data) {
	// this pattern is to check for '"' IDENT '"'
	regex identQuotePattern("\"[A-Za-z]([A-Za-z0-9])*\"");

	return isSynonym(data) || data == "_" || std::regex_match(data, identQuotePattern);
}

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
