#pragma once

#include <unordered_map>
#include <unordered_set>

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"

using std::unordered_map, std::unordered_set;

// mini simpler state
typedef unordered_map<PQLTokenType, unordered_set<PQLTokenType>> PredictiveMap;

class DeclarativeParserState : public IParserState {
private:
	unique_ptr<PQLParserContext>& parserContext;
	unique_ptr<PQLTokenStream>& tokenStream;
	static PQLTokenType exitToken;
	static PredictiveMap predictiveMap;

public:
	explicit DeclarativeParserState(PQLParserContext& parserContext);
	void handleToken(PQLTokenType tokenType) override;
};
