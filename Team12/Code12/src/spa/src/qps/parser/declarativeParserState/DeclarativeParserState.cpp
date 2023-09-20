#include "DeclarativeParserState.h"
#include <iostream>

#include "qps/exceptions/QPSInvalidQueryException.h"

PredictiveMap DeclarativeParserState::predictiveMap = {
	{ PQL_NAME_TOKEN, { PQL_ENTITY_TOKEN, PQL_SYNONYM_TOKEN, PQL_SELECT_TOKEN } }, // name token can be upgraded to either
	{ PQL_ENTITY_TOKEN, { PQL_NAME_TOKEN } },
	{ PQL_SYNONYM_TOKEN, { PQL_COMMA_TOKEN, PQL_SEMICOLON_TOKEN } },
	{ PQL_COMMA_TOKEN, { PQL_NAME_TOKEN } },
	{ PQL_SEMICOLON_TOKEN, { PQL_ENTITY_TOKEN, PQL_NAME_TOKEN } }
};

DeclarativeParserState::DeclarativeParserState(PQLParserContext& parserContext) :
    parserContext(parserContext),
	tokenStream(parserContext.getTokenStream()),
	currentEntity(""),
	prev(PQL_NULL_TOKEN) {}

// To identify what type is the name token
void DeclarativeParserState::processNameToken(PQLToken& curr)
{
	if (curr.getType() != PQL_NAME_TOKEN) {
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
	}

	if (prev == PQL_NULL_TOKEN // first token of this clause. Must be ENTITY
		|| prev == PQL_SEMICOLON_TOKEN // next must be either SELECT or SYNONYM
		|| currentEntity == "")
	{
		auto entity = keywordToTokenType.find(curr.getValue());
		if (entity != keywordToTokenType.end()) {
			curr.updateTokenType(entity->second);
		}
	} else {
		curr.updateTokenType(PQL_SYNONYM_TOKEN);
	}
}

bool DeclarativeParserState::isExpectedToken(PQLTokenType curr) {
	auto nextTokens = predictiveMap.find(this->prev);

	if (nextTokens == predictiveMap.end()) {
		return false;
	}
    auto nextStep = nextTokens->second;
	if (nextStep.find(curr) == nextStep.end()) {
		return false;
	}
	return true;
}

void DeclarativeParserState::handleToken() {

	while (!this->tokenStream.isTokenStreamEnd()) {
        PQLToken& curr = tokenStream.getCurrentToken();

		if (!isExpectedToken(curr.getType())) {
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
		}

		switch (curr.getType()) {
		case PQL_NAME_TOKEN:
			processNameToken(curr);
			break;
		case PQL_ENTITY_TOKEN:
			this->currentEntity = curr.getValue();
			break;
		case PQL_SYNONYM_TOKEN:
			this->parserContext.addToContext(this->currentEntity, curr.getValue());
			break;
		case PQL_COMMA_TOKEN:
		case PQL_SEMICOLON_TOKEN:
			break;
		case PQL_SELECT_TOKEN: // exit token
			// TODO: Select state
            // add to clause
//			this->parserContext.transitionTo();

			return;
		default:
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);
		}
		this->prev = curr.getType();
		tokenStream.next();
	}
}

