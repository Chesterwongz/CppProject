#include "SelectParserState.h"

#include "qps/parser/suchThatParserState/SuchThatParserState.h"
#include "qps/parser/patternParserState/PatternParserState.h"

PredictiveMap SelectParserState::predictiveMap = {
    { PQL_NULL_TOKEN, { PQL_SELECT_TOKEN } }, // Select should have been processed by previous state to be transitioned here
	{ PQL_SELECT_TOKEN, { PQL_SYNONYM_TOKEN } },
	{ PQL_SYNONYM_TOKEN, { PQL_COMMA_TOKEN, PQL_SUCH_TOKEN,
                           PQL_SEMICOLON_TOKEN, PQL_PATTERN_TOKEN } }
};

PQLTokenType SelectParserState::exitToken = PQL_SYNONYM_TOKEN;

SelectParserState::SelectParserState(PQLParserContext& parserContext) :
        BaseParserState(parserContext) {}


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
            throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
		}

		switch (curr.getType()) {
		case PQL_SYNONYM_TOKEN:
            parserContext.addSelectSynonym(curr.getValue());
            break;
		case PQL_SELECT_TOKEN:
            break;
        case PQL_SUCH_TOKEN:
            parserContext.transitionTo(
                std::make_unique<SuchThatParserState>(parserContext));
            return;
        case PQL_PATTERN_TOKEN:
            parserContext.transitionTo(std::make_unique<PatternParserState>(parserContext));
            return;
		default:
            throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
		}
        this->prev = curr.getType();
        tokenStream.next();
	}
    if (prev != exitToken) {
        throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_SELECT);
    }
}
