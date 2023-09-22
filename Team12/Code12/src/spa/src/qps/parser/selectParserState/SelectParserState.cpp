#include "SelectParserState.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/parser/suchThatParserState//SuchThatParserState.h"
#include "qps/clause/selectClause/SelectClause.h"

PredictiveMap SelectParserState::predictiveMap = {
    { PQL_NULL_TOKEN, {PQL_SELECT_TOKEN} }, // Select should have been processed by previous state to be transitioned here
	{ PQL_SELECT_TOKEN, { PQL_SYNONYM_TOKEN } },
	{ PQL_SYNONYM_TOKEN, { PQL_SUCH_TOKEN, PQL_PATTERN_TOKEN } }
};

PQLTokenType SelectParserState::exitToken = PQL_SYNONYM_TOKEN;

SelectParserState::SelectParserState(PQLParserContext& parserContext) :
        parserContext(parserContext),
        tokenStream(parserContext.getTokenStream()),
        prev(PQL_NULL_TOKEN) {}


void SelectParserState::processNameToken(PQLToken& curr)
{
	if (prev == PQL_SELECT_TOKEN) {
        curr.updateTokenType(PQL_SYNONYM_TOKEN);
	} else {
        PQLTokenType toUpdate = PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
        curr.updateTokenType(toUpdate);
    }
}

void SelectParserState::handleToken() {

	while (!this->tokenStream.isTokenStreamEnd()) {
		auto& curr = tokenStream.getCurrentToken();

        if (curr.getType() == PQL_NAME_TOKEN) {
            processNameToken(curr);
        }

		if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
		}

		switch (curr.getType()) {
		case PQL_SYNONYM_TOKEN:
			this->parserContext.transitionTo(make_unique<SuchThatParserState>(parserContext));
            parserContext.addClause(make_unique<SelectClause>(curr.getValue()));
			return;
		case PQL_SELECT_TOKEN:
            break;
        case PQL_SUCH_TOKEN:
            parserContext.transitionTo(make_unique<SuchThatParserState>(parserContext));
            return;
            // PATTERN token case
		default:
			throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);
		}
        this->prev = curr.getType();
        tokenStream.next();
	}
    if (prev != exitToken) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_INCOMPLETE_QUERY);
    }
}
