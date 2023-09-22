#pragma once

#include <memory>

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"

using std::make_unique;

class DeclarativeParserState : public IParserState {
private:
	PQLParserContext& parserContext;
	PQLTokenStream& tokenStream;
	PQLTokenType prev;
	string currentEntity;
	static PredictiveMap predictiveMap;
	void processNameToken(PQLToken& curr) override;

public:
	explicit DeclarativeParserState(PQLParserContext& parserContext);
	void handleToken() override;
    ~DeclarativeParserState() override = default;
};
