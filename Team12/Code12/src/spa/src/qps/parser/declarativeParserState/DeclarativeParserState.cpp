#include "DeclarativeParserState.h"

#include "qps/parser/selectParserState/SelectParserState.h"

PredictiveMap DeclarativeParserState::predictiveMap = {
    { PQL_NULL_TOKEN, { PQL_ENTITY_TOKEN } },
    { PQL_ENTITY_TOKEN, { PQL_SYNONYM_TOKEN } },
	{ PQL_SYNONYM_TOKEN, { PQL_COMMA_TOKEN, PQL_SEMICOLON_TOKEN } },
	{ PQL_COMMA_TOKEN, { PQL_SYNONYM_TOKEN } },
	{ PQL_SEMICOLON_TOKEN, { PQL_ENTITY_TOKEN, PQL_SELECT_TOKEN } }
};

DeclarativeParserState::DeclarativeParserState(PQLParserContext& parserContext) :
        BaseParserState(parserContext) {}

// To identify what type is the name token
void DeclarativeParserState::processNameToken(PQLToken& curr)
{
    if (prev == PQL_ENTITY_TOKEN || prev == PQL_COMMA_TOKEN) {
        curr.updateTokenType(PQL_SYNONYM_TOKEN);
    } else {
        auto tokenType = PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
        curr.updateTokenType(tokenType);
    }
}

void DeclarativeParserState::handleToken() {
	while (!this->tokenStream.isTokenStreamEnd()) {
        PQLToken& curr = tokenStream.getCurrentToken();

        // always upgrade name token before doing any checks
        if (curr.getType() == PQL_NAME_TOKEN) {
            processNameToken(curr);
        }

		if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
			throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
		}

		switch (curr.getType()) {
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
			this->parserContext.transitionTo(make_unique<SelectParserState>(parserContext));
            return;
		default:
            throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
		}
        this->prev = curr.getType();
        tokenStream.next();
	}

    // should never exit in this parser
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_DECLARATION);
}

