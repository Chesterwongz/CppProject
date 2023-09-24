#pragma once

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"

using std::make_unique;

class SelectParserState : public IParserState {
private:
	PQLParserContext& parserContext;
	PQLTokenStream& tokenStream;
	PQLTokenType prev;
	static PredictiveMap predictiveMap;
	static PQLTokenType exitToken;
	void processNameToken(PQLToken& curr) override;

public:
	explicit SelectParserState(PQLParserContext& parserContext);
	void handleToken() override;
    ~SelectParserState() override = default;
};
