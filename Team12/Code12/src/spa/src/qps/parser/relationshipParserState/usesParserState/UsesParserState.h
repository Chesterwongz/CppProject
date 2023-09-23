#pragma once

#include <memory>

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/relationshipParserState/RelationshipParserState.h"

using std::make_unique, std::unique_ptr;

class UsesParserState : public RelationshipParserState {
private:
    PQLParserContext& parserContext;
    PQLTokenStream& tokenStream;
    PQLTokenType prev;
    static PredictiveMap predictiveMap;
    static PQLTokenType exitToken;
    static size_t maxNumberOfArgs;

public:
    explicit UsesParserState(PQLParserContext& parserContext);
    void handleToken() override;
    ~UsesParserState() override = default;
};
