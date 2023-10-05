#pragma once

#include "IParserState.h"
#include "PQLParserContext.h"
#include "qps/clause/Clause.h"

class BaseParserState : public IParserState {
protected:
    PQLParserContext& parserContext;
    PQLTokenStream& tokenStream;
    PQLTokenType prev;

public:
    explicit BaseParserState(PQLParserContext &parserContext);
    ~BaseParserState() override = default;
};
