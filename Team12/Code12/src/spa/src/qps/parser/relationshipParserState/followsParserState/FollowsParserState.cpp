#include "FollowsParserState.h"

#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/parser/patternParserState/PatternParserState.h"

// TODO: create such that clause after merge
PredictiveMap FollowsParserState::predictiveMap = {
        { PQL_NULL_TOKEN, { PQL_FOLLOWS_TOKEN } },
        { PQL_FOLLOWS_TOKEN, { PQL_ASTERISKS_TOKEN, PQL_OPEN_BRACKET_TOKEN } },
        { PQL_ASTERISKS_TOKEN, { PQL_OPEN_BRACKET_TOKEN } },
        { PQL_OPEN_BRACKET_TOKEN, { PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_INTEGER_TOKEN } },
        { PQL_SYNONYM_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_WILDCARD_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_INTEGER_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_COMMA_TOKEN, { PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_INTEGER_TOKEN } },
        { PQL_CLOSE_BRACKET_TOKEN, { PQL_PATTERN_TOKEN } }
};

PQLTokenType FollowsParserState::exitToken = PQL_CLOSE_BRACKET_TOKEN;

int FollowsParserState::maxNumberOfArgs = 2;

FollowsParserState::FollowsParserState(PQLParserContext &parserContext) :
    parserContext(parserContext),
    tokenStream(this->parserContext.getTokenStream()),
    prev(PQL_NULL_TOKEN),
    isInBracket(false),
    isTransitive(false) {};

void FollowsParserState::processNameToken(PQLToken &curr) {
    if (isInBracket) {
        curr.updateTokenType(PQL_SYNONYM_TOKEN);
        return;
    }
    curr.updateTokenType(PQLParserUtils::getTokenTypeFromKeyword(curr.getValue()));
}

void FollowsParserState::handleToken() {
    while (!this->tokenStream.isTokenStreamEnd()) {
        auto& curr = tokenStream.getCurrentToken();

        if (curr.getType() == PQL_NAME_TOKEN) {
            processNameToken(curr);
        }

        if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
            throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
        }

        switch (curr.getType()) {
            case PQL_FOLLOWS_TOKEN:
            case PQL_COMMA_TOKEN:
                break;
            case PQL_ASTERISKS_TOKEN:
                isTransitive = true;
                break;
            case PQL_OPEN_BRACKET_TOKEN:
                isInBracket = true;
                break;
            case PQL_CLOSE_BRACKET_TOKEN:
                isInBracket = false;
                // TODO: add clause
                break;
            case PQL_SYNONYM_TOKEN:
            case PQL_INTEGER_TOKEN:
            case PQL_WILDCARD_TOKEN:
                // TODO: create arguments and add to arguments vector
                break;
            case PQL_PATTERN_TOKEN:
                this->parserContext.transitionTo(make_unique<PatternParserState>(parserContext));
                return;
            default:
                throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
        }
        this->prev = curr.getType();
        tokenStream.next();
    }
    if (prev != exitToken || isInBracket) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNMATCHED_BRACKET);
    }
}
