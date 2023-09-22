#include "ModifiesParserState.h"

#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/parser/patternParserState/PatternParserState.h"

PredictiveMap ModifiesParserState::predictiveMap = {
        { PQL_NULL_TOKEN, { PQL_MODIFIES_TOKEN } },
        { PQL_MODIFIES_TOKEN, { PQL_OPEN_BRACKET_TOKEN } },
        { PQL_OPEN_BRACKET_TOKEN, { PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN,
                                  PQL_LITERAL_REF_TOKEN, PQL_INTEGER_TOKEN} },
        { PQL_COMMA_TOKEN, { PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN,
                             PQL_LITERAL_REF_TOKEN } },
        { PQL_SYNONYM_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_WILDCARD_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_LITERAL_REF_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_INTEGER_TOKEN, { PQL_COMMA_TOKEN } },
        { PQL_CLOSE_BRACKET_TOKEN, { PQL_PATTERN_TOKEN } }
};

PQLTokenType ModifiesParserState::exitToken = PQL_CLOSE_BRACKET_TOKEN;

int ModifiesParserState::maxNumberOfArgs = 2;

ModifiesParserState::ModifiesParserState(PQLParserContext &parserContext) :
        parserContext(parserContext),
        tokenStream(this->parserContext.getTokenStream()),
        prev(PQL_NULL_TOKEN),
        isInBracket(false) {};

void ModifiesParserState::processNameToken(PQLToken &curr) {
    if (isInBracket) {
        curr.updateTokenType(PQL_SYNONYM_TOKEN);
        return;
    }
    curr.updateTokenType(PQLParserUtils::getTokenTypeFromKeyword(curr.getValue()));
}

void ModifiesParserState::handleToken() {
    while (!this->tokenStream.isTokenStreamEnd()) {
        auto& curr = tokenStream.getCurrentToken();

        if (curr.getType() == PQL_NAME_TOKEN) {
            processNameToken(curr);
        }

        if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
            throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
        }

        switch (curr.getType()) {
            case PQL_MODIFIES_TOKEN:
            case PQL_COMMA_TOKEN:
                break;
            case PQL_OPEN_BRACKET_TOKEN:
                isInBracket = true;
                break;
            case PQL_CLOSE_BRACKET_TOKEN:
                isInBracket = false;
                // TODO: add clause
                break;
            case PQL_SYNONYM_TOKEN:
            case PQL_WILDCARD_TOKEN:
            case PQL_LITERAL_REF_TOKEN:
            case PQL_INTEGER_TOKEN:
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

