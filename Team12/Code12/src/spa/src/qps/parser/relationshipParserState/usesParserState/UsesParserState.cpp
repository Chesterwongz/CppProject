#include "UsesParserState.h"

#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/argument/argumentFactory/ArgumentFactory.h"
#include "qps/parser/patternParserState/PatternParserState.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"

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
        { PQL_INTEGER_TOKEN, { PQL_COMMA_TOKEN } },
        { PQL_CLOSE_BRACKET_TOKEN, { PQL_PATTERN_TOKEN } }
};

PQLTokenType UsesParserState::exitToken = PQL_CLOSE_BRACKET_TOKEN;

size_t UsesParserState::maxNumberOfArgs = 2;

UsesParserState::UsesParserState(PQLParserContext &parserContext) :
        parserContext(parserContext),
        tokenStream(this->parserContext.getTokenStream()),
        prev(PQL_NULL_TOKEN),
        RelationshipParserState(false) {};

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
                parserContext.addClause(make_unique<SuchThatClause>(
                        USES_ENUM,
                        std::move(arguments.at(0)),
                        std::move(arguments.at(1)),
                        false
                ));
                break;
            case PQL_SYNONYM_TOKEN:
                arguments.push_back(std::move(ArgumentFactory::createSynonymArgument(curr.getValue())));
                break;
            case PQL_WILDCARD_TOKEN:
                arguments.push_back(std::move(ArgumentFactory::createWildcardArgument()));
                break;
            case PQL_LITERAL_REF_TOKEN:
                arguments.push_back(std::move(ArgumentFactory::createIdentArgument(curr.getValue())));
                break;
            case PQL_INTEGER_TOKEN:
                arguments.push_back(std::move(ArgumentFactory::createIntegerArgument(curr.getValue())));
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
    if (!isSafeExit(maxNumberOfArgs, arguments.size())) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNMATCHED_BRACKET);
    }
}
