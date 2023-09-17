#include "DeclarativeParserState.h"

PQLTokenType DeclarativeParserState::exitToken = PQL_SELECT_TOKEN;

PredictiveMap DeclarativeParserState::predictiveMap = {
	PQL_ENTITY_TOKEN, { PQL_NAME_TOKEN },
	PQL_SYNONYM_TOKEN, { PQL_COMMA_TOKEN, PQL_SEMICOLON_TOKEN },
	PQL_COMMA_TOKEN, { PQL_NAME_TOKEN },
	PQL_SEMICOLON_TOKEN, { PQL_ENTITY_TOKEN, PQL_SELECT_TOKEN }
};

DeclarativeParserState::DeclarativeParserState(PQLParserContext& parserContext)
{
	this->parserContext = parserContext;
	this->tokenStream = parserContext.getTokenStream();
}



