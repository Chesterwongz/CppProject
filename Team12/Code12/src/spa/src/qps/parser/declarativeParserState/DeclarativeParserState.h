#pragma once

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"

class DeclarativeParserState : public IParserState {
private:
	unique_ptr<PQLParserContext>& parserContext;
	unique_ptr<PQLTokenStream>& tokenStream;

public:
	explicit DeclarativeParserState(unique_ptr<PQLParserContext>& parserContext);

};
