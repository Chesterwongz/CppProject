#include "UsesParserState.h"

#include "qps/exceptions/QPSInvalidQueryException.h"

PredictiveMap UsesParserState::predictiveMap = {
        { PQL_NULL_TOKEN, { PQL_USES_TOKEN } },
        { PQL_USES_TOKEN, { PQL_OPEN_BRACKET_TOKEN } },
        { PQL_OPEN_BRACKET_TOKEN, { PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN,
                                    PQL_LITERAL_REF_TOKEN, PQL_INTEGER_TOKEN} },
        { PQL_COMMA_TOKEN, { PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN,
                            PQL_LITERAL_REF_TOKEN } },
        { PQL_SYNONYM_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_WILDCARD_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_LITERAL_REF_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_INTEGER_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_CLOSE_BRACKET_TOKEN, { PQL_PATTERN_TOKEN } }
};

PQLTokenType UsesParserState::exitToken = PQL_CLOSE_BRACKET_TOKEN;

int UsesParserState::maxNumberOfArgs = 2;

UsesParserState::UsesParserState(PQLParserContext &parserContext) :
        parserContext(parserContext),
        tokenStream(this->parserContext.getTokenStream()),
        prev(PQL_NULL_TOKEN),
        isInBracket(false) {};

void UsesParserState::processNameToken(PQLToken &curr) {
    if (isInBracket) {
        curr.updateTokenType(PQL_SYNONYM_TOKEN);
        return;
    }
    curr.updateTokenType(PQLParserUtils::getTokenTypeFromKeyword(curr.getValue()));
}

void UsesParserState::handleToken() {
    while (!this->tokenStream.isTokenStreamEnd()) {
        auto& curr = tokenStream.getCurrentToken();

        if (curr.getType() == PQL_NAME_TOKEN) {
            processNameToken(curr);
        }

        if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
            throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
        }

        switch (curr.getType()) {
            case PQL_USES_TOKEN:
            case PQL_COMMA_TOKEN:
                break;
            case PQL_OPEN_BRACKET_TOKEN:
                isInBracket = true;
                break;
            case PQL_CLOSE_BRACKET_TOKEN:
                isInBracket = false;
                // TODO: add clause
                // TODO: transitionTo
                return;
            case PQL_SYNONYM_TOKEN:
            case PQL_WILDCARD_TOKEN:
            case PQL_LITERAL_REF_TOKEN:
            case PQL_INTEGER_TOKEN:
                // TODO: create arguments and add to arguments vector
                break;
            default:
                throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
        }
        if (prev != exitToken && isInBracket) {
            throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNMATCHED_BRACKET);
        }
    }
}
