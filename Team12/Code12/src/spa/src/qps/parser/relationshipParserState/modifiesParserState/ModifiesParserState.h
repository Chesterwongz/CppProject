#pragma once

#include <memory>

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"

using std::make_unique, std::unique_ptr;

class ModifiesParserState : public IParserState {
private:
    PQLParserContext& parserContext;
    PQLTokenStream& tokenStream;
    PQLTokenType prev;
    bool isInBracket;
    static PredictiveMap predictiveMap;
    static PQLTokenType exitToken;
    static int maxNumberOfArgs;
//    vector<IArguments> arguments;
    void processNameToken(PQLToken& curr) override;

public:
    explicit ModifiesParserState(PQLParserContext& parserContext);
    void handleToken() override;
    ~ModifiesParserState() override = default;
};
