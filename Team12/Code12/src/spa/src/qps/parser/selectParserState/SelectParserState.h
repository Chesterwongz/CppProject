#pragma once

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/BaseParserState.h"

class SelectParserState : public BaseParserState {
private:
	static PredictiveMap predictiveMap;
	static PQLTokenType exitToken;
	void processNameToken(PQLToken& curr) override;

public:
	explicit SelectParserState(PQLParserContext& parserContext);
	void handleToken() override;
    ~SelectParserState() override = default;
};
