#include "PatternParserState.h"

#include "qps/exceptions/QPSInvalidQueryException.h"

PredictiveMap PatternParserState::predictiveMap = {
        { PQL_NULL_TOKEN, { PQL_PATTERN_TOKEN } },
        { PQL_PATTERN_TOKEN, { PQL_SYNONYM_TOKEN } }, // must be assign
        { PQL_SYNONYM_TOKEN, { PQL_OPEN_BRACKET_TOKEN, PQL_COMMA_TOKEN } },
        { PQL_OPEN_BRACKET_TOKEN, { PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN } },
        { PQL_WILDCARD_TOKEN, { PQL_COMMA_TOKEN, PQL_LITERAL_REF_TOKEN,
                                PQL_LITERAL_EXPRESSION_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_LITERAL_REF_TOKEN, { PQL_COMMA_TOKEN, PQL_WILDCARD_TOKEN,
                                   PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_COMMA_TOKEN, { PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN, PQL_LITERAL_EXPRESSION_TOKEN } },
        { PQL_LITERAL_EXPRESSION_TOKEN, { PQL_WILDCARD_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_CLOSE_BRACKET_TOKEN, { PQL_SUCH_TOKEN } }
};

PQLTokenType PatternParserState::exitToken = PQL_CLOSE_BRACKET_TOKEN;

PatternParserState::PatternParserState(PQLParserContext& parserContext) :
        parserContext(parserContext),
        tokenStream(parserContext.getTokenStream()),
        prev(PQL_NULL_TOKEN),
        isInBracket(false),
        argumentCount(0) {}

void PatternParserState::processNameToken(PQLToken &curr) {
    if (prev == PQL_OPEN_BRACKET_TOKEN) {
        curr.updateTokenType(PQL_SYNONYM_TOKEN);
    } else {
        PQLTokenType toUpdate = PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
        curr.updateTokenType(toUpdate);
    }
}

void PatternParserState::processSynonymToken(PQLToken& curr) {
    string synType = parserContext.getSynonymType(curr.getValue());

    if (prev == PQL_PATTERN_TOKEN && outerSynonym.empty()) {
        if (synType == ASSIGN_KEYWORD) {
            outerSynonym == curr.getValue();
        } else {
            throw QPSInvalidQueryException(QPS_INVALID_QUERY_INVALID_PATTERN_SYNONYM);
        }
    } else if (argumentCount == 0) {
        addAsArgument(curr);
    }
    throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
}

void PatternParserState::addAsArgument(PQLToken &curr) {
    // add to vector of arguments
}

void PatternParserState::handleToken() {
    while (!this->tokenStream.isTokenStreamEnd()) {
        auto& curr = tokenStream.getCurrentToken();

        if (curr.getType() == PQL_NAME_TOKEN) {
            processNameToken(curr);
        }

        if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
            throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
        }

        switch (curr.getType()) {
            case PQL_PATTERN_TOKEN:
                break;
            case PQL_COMMA_TOKEN:
                argumentCount++;
                break;
            case PQL_SYNONYM_TOKEN:
                processSynonymToken(curr);
                break;
            case PQL_OPEN_BRACKET_TOKEN:
                isInBracket = true;
                break;
            case PQL_CLOSE_BRACKET_TOKEN:
                isInBracket = false;
                // transitionTo
                return;
            default:
                throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);
        }
        this->prev = curr.getType();
        tokenStream.next();
    }
    if (prev != exitToken && isInBracket) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNMATCHED_BRACKET);
    }
}
