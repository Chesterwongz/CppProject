#pragma once

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"

class DeclarativeParserState : public IParserState {
private:
	PQLParserContext& parserContext;
	PQLTokenStream& tokenStream;
	PQLTokenType prev;
	string currentEntity;
	static PredictiveMap predictiveMap;
	void processNameToken(PQLToken& curr);
	bool isExpectedToken(PQLTokenType curr) override;

public:
	explicit DeclarativeParserState(PQLParserContext& parserContext);
	void handleToken() override;
};
