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

DeclarativeParserState::DeclarativeParserState(PQLParserContext& parserContext)
{
	this->parserContext = parserContext;
	this->tokenStream = parserContext.getTokenStream();
	this->currentEntity = nullptr;
	this->prev = nullptr;
}

// To identify what type is the name token
void DeclarativeParserState::processNameToken(unique_ptr<PQLToken>& curr)
{
	if (token->getType != PQL_NAME_TOKEN) {
		throw QPSInvalidQueryException();
	}

	if (prev == nullptr // first token of this clause. Must be ENTITY
		|| prev->getType() == PQL_SEMICOLON_TOKEN // next must be either SELECT or SYNONYM
		|| currentEntity == nullptr)
	{
		auto entity = keywordToTokenType.find(curr->getValue);
		if (entity != keywordToTokenType.end()) {
			std::cout << entity << std::endl;
			curr->updateTokenType(entity);
		}
	} else {
		curr->updateTokenType(PQL_SYNONYM_TOKEN);
	}
}

bool DeclarativeParserState::isExpectedToken(PQLTokenType curr) {
	auto nextTokens = predictiveMap.find(this->prev);

	if (nextTokens == predictiveMap.end()) {
		return false;
	}
	if (nextTokens.find(curr) == nextTokens.end()) {
		return false;
	}
	return true;
}

void DeclarativeParserState::handleToken() {

	while (!this->tokenStream->isTokenStreamEnd()) {
		auto curr = tokenStream->getCurrentToken();

		if (!isExpectedToken(curr->getType())) {
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
		}

		switch (curr->getType()) {
		case PQL_NAME_TOKEN:
			processNameToken(curr);
			break;
		case PQL_ENTITY_TOKEN:
			this->currentEntity = curr->getValue();
			break;
		case PQL_SYNONYM_TOKEN:
			this->parserContext->addToContext(this->currentEntity, curr->getValue());
			break;
		case PQL_COMMA_TOKEN:
		case PQL_SEMICOLON_TOKEN:
			break;
		case PQL_SELECT_TOKEN:
			// TODO: Select state
			this->parserContext->transitionTo();
			return;
		default:
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);
		}
		this->prev = curr;
		tokenStream->next();
	}
}

