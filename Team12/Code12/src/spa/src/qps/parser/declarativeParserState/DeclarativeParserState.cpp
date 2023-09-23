#include "DeclarativeParserState.h"

#include <iostream>

#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/parser/selectParserState/SelectParserState.h"

PredictiveMap DeclarativeParserState::predictiveMap = {
    { PQL_NULL_TOKEN, { PQL_ENTITY_TOKEN } },
    { PQL_ENTITY_TOKEN, { PQL_SYNONYM_TOKEN } },
	{ PQL_SYNONYM_TOKEN, { PQL_COMMA_TOKEN, PQL_SEMICOLON_TOKEN } },
	{ PQL_COMMA_TOKEN, { PQL_SYNONYM_TOKEN } },
	{ PQL_SEMICOLON_TOKEN, { PQL_ENTITY_TOKEN, PQL_SELECT_TOKEN } }
};

DeclarativeParserState::DeclarativeParserState(PQLParserContext& parserContext) :
    parserContext(parserContext),
	tokenStream(parserContext.getTokenStream()),
	prev(PQL_NULL_TOKEN) {}

// To identify what type is the name token
void DeclarativeParserState::processNameToken(PQLToken& curr)
{
    if (prev == PQL_ENTITY_TOKEN) {
        curr.updateTokenType(PQL_SYNONYM_TOKEN);
    } else {
        auto tokenType = PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
        curr.updateTokenType(tokenType);
    }
}

void DeclarativeParserState::handleToken() {
    std::cout << "Processing in Declarative Parser State" << std::endl;

	while (!this->tokenStream.isTokenStreamEnd()) {
        PQLToken& curr = tokenStream.getCurrentToken();

        // always upgrade name token before doing any checks
        if (curr.getType() == PQL_NAME_TOKEN) {
            processNameToken(curr);
        }

		if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
		}

		switch (curr.getType()) {
		case PQL_ENTITY_TOKEN:
			this->currentEntity = curr.getValue();
			break;
		case PQL_SYNONYM_TOKEN:
            std::cout << "Adding synonym: " << curr.getValue() << " of type: " << currentEntity << " to context" << std::endl;
			this->parserContext.addToContext(this->currentEntity, curr.getValue());
            break;
		case PQL_COMMA_TOKEN:
		case PQL_SEMICOLON_TOKEN:
			break;
		case PQL_SELECT_TOKEN: // exit token
			this->parserContext.transitionTo(make_unique<SelectParserState>(parserContext));
            std::cout << "Transitioning to Select Parser State" << std::endl;
			return;
		default:
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);
		}
        this->prev = curr.getType();
        tokenStream.next();
	}

    // should never exit in this parser
    throw QPSInvalidQueryException(QPS_INVALID_QUERY_INCOMPLETE_QUERY);
}

