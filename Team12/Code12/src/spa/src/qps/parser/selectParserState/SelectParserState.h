#pragma once

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"

class SelectParserState : public IParserState {
private:
	unique_ptr<PQLParserContext>& parserContext;
	unique_ptr<PQLTokenStream>& tokenStream;
	unique_ptr<PQLToken>& prev;
	static PredictiveMap predictiveMap;
	void processNameToken(unique_ptr<PQLToken>& curr);
	bool isExpectedToken(PQLTokenType curr) override;

public:
	explicit SelectParserState(PQLParserContext& parserContext);
	void handleToken(PQLTokenType tokenType) override;
};
