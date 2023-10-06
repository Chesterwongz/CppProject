#include "RelationshipParserState.h"
#include "qps/common/PQLParserUtils.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

int RelationshipParserState::expectedNumberOfArgs = 2;

RelationshipParserState::RelationshipParserState(PQLParserContext &parserContext, bool isInBracket) :
isInBracket(isInBracket),
relationship(""),
BaseParserState(parserContext) {}

void RelationshipParserState::processNameToken(PQLToken &curr) {
    if (this->isInBracket) {
        if (QPSStringUtils::isSynonym(curr.getValue())){
            curr.updateTokenType(PQL_SYNONYM_TOKEN);
        } else {
            curr.updateTokenType(PQL_NULL_TOKEN);
        }
        return;
    }
    curr.updateTokenType(PQLParserUtils::getTokenTypeFromKeyword(curr.getValue()));
}

bool RelationshipParserState::checkSafeExit(ArgumentList &arguments) {
    if (arguments.size() != expectedNumberOfArgs) {
        throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
    }
    return true;
}

Abstraction RelationshipParserState::getAbstractionType(const std::string &keyword, unordered_map<string,
                                                        Abstraction> abstractionKeywordMap) {
    auto mapRes = abstractionKeywordMap.find(keyword);
    if (mapRes == abstractionKeywordMap.end()) {
        throw QPSSyntaxError(QPS_TOKENIZATION_ERR + keyword);
    }
    return mapRes->second;
}
