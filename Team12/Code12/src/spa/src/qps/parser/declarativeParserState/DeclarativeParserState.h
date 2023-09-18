#pragma once

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"

class DeclarativeParserState : public IParserState {
private:
	unique_ptr<PQLParserContext>& parserContext;
	unique_ptr<PQLTokenStream>& tokenStream;
	unique_ptr<PQLToken>& prev;
	string currentEntity;
	static PredictiveMap predictiveMap;
	void processNameToken(unique_ptr<PQLToken>& curr);
	bool isExpectedToken(PQLTokenType curr) override;

public:
	explicit DeclarativeParserState(PQLParserContext& parserContext);
	void handleToken(PQLTokenType tokenType) override;
};
