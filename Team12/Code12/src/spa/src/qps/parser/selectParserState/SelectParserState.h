#pragma once

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"

class SelectParserState : public IParserState {
private:
	PQLParserContext& parserContext;
	PQLTokenStream& tokenStream;
	PQLTokenType prev;
	static PredictiveMap predictiveMap;
	void processNameToken(PQLToken& curr);
	bool isExpectedToken(PQLTokenType curr) override;

public:
	explicit SelectParserState(PQLParserContext& parserContext);
	void handleToken() override;
};
