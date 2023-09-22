#pragma once

#include <memory>

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"

using std::make_unique, std::unique_ptr;

class FollowsParserState : public IParserState {
private:
    PQLParserContext& parserContext;
    PQLTokenStream& tokenStream;
    PQLTokenType prev;
    bool isInBracket;
    bool isTransitive;
    static PredictiveMap predictiveMap;
    static PQLTokenType exitToken;
    static int maxNumberOfArgs;
//    vector<IArguments> arguments;
    void processNameToken(PQLToken& curr) override;

public:
    explicit FollowsParserState(PQLParserContext& parserContext);
    void handleToken() override;
    ~FollowsParserState() override = default;
};
