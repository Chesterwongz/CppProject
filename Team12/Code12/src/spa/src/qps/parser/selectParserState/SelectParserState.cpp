#include "SelectParserState.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

// TODO
PredictiveMap SelectParserState::predictiveMap = {
	{ PQL_NAME_TOKEN, { PQL_SYNONYM_TOKEN } }, // name token can be upgraded to either
	{ PQL_SELECT_TOKEN, { PQL_NAME_TOKEN } }
};

SelectParserState::SelectParserState(PQLParserContext& parserContext) :
        parserContext(parserContext),
        tokenStream(parserContext.getTokenStream()),
        prev(PQL_NULL_TOKEN) {}

// To identify what type is the name token
void SelectParserState::processNameToken(PQLToken& curr)
{
	if (curr.getType() != PQL_NAME_TOKEN) {
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
	}

	if (prev == PQL_SELECT_TOKEN)
	{
		curr.updateTokenType(PQL_SYNONYM_TOKEN);
	}
}

bool SelectParserState::isExpectedToken(PQLTokenType curr) {
	// TODO: Seems buggy...
	auto nextTokens = predictiveMap.find(this->prev);

	if (nextTokens == predictiveMap.end()) {
		return false;
	}
    auto nextSteps = nextTokens->second;
	if (nextSteps.find(curr) == nextSteps.end()) {
		return false;
	}
	return true;
}

void SelectParserState::handleToken() {

	while (!this->tokenStream.isTokenStreamEnd()) {
		auto& curr = tokenStream.getCurrentToken();

		if (!isExpectedToken(curr.getType())) {
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
		}

		switch (curr.getType()) {
		case PQL_NAME_TOKEN:
			processNameToken(curr);
			break;
		case PQL_SYNONYM_TOKEN:
			// TODO: Depends on next type
//			this->parserContext.transitionTo();
			return;
		case PQL_SELECT_TOKEN:
			
		default:
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);
		}
		this->prev = curr.getType();
		tokenStream.next();
	}
}
