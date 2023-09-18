#include "SelectParserState.h"

// TODO
PredictiveMap SelectParserState::predictiveMap = {
	{ PQL_NAME_TOKEN, { PQL_SYNONYM_TOKEN } }, // name token can be upgraded to either
	{ PQL_SELECT_TOKEN, { PQL_NAME_TOKEN } }
};

SelectParserState::SelectParserState(PQLParserContext& parserContext)
{
	this->parserContext = parserContext;
	this->tokenStream = parserContext.getTokenStream();
	this->prev = nullptr;
}

// To identify what type is the name token
void SelectParserState::processNameToken(unique_ptr<PQLToken>& curr)
{
	if (token->getType != PQL_NAME_TOKEN) {
		throw QPSInvalidQueryException();
	}

	if (prev->getType() == PQL_SELECT_TOKEN)
	{
		curr->updateTokenType(PQL_SYNONYM_TOKEN);
	}
}

bool SelectParserState::isExpectedToken(PQLTokenType curr) {
	// TODO: Seems buggy...
	auto nextTokens = predictiveMap.find(this->prev);

	if (nextTokens == predictiveMap.end()) {
		return false;
	}
	if (nextTokens.find(curr) == nextTokens.end()) {
		return false;
	}
	return true;
}

void SelectParserState::handleToken() {

	while (!this->tokenStream->isTokenStreamEnd()) {
		auto curr = tokenStream->getCurrentToken();

		if (!isExpectedToken(curr->getType())) {
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
		}

		switch (curr->getType()) {
		case PQL_NAME_TOKEN:
			processNameToken(curr);
			break;
		case PQL_SYNONYM_TOKEN:
			// TODO: Depends on next type
			this->parserContext->transitionTo();
			return;
		case PQL_SELECT_TOKEN:
			
		default:
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);
		}
		this->prev = curr;
		tokenStream->next();
	}
}
