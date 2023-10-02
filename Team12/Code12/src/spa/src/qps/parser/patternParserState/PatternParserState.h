#pragma once

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"
#include "qps/argument/AbstractArgument.h"

using std::make_unique, std::unique_ptr;

class PatternParserState : public IParserState {
private:
    PQLParserContext& parserContext;
    PQLTokenStream& tokenStream;
    PQLTokenType prev;
    bool isInBracket;
    string matchPattern;
    int partialMatchWildCardCount;
    int argumentCount;
    unique_ptr<AbstractArgument> outerSynonym;
    static PredictiveMap predictiveMap;
    static PQLTokenType exitToken;
    static size_t maxNumberOfArgs;
    vector<unique_ptr<AbstractArgument>> patternArg;
    void processNameToken(PQLToken& curr) override;
    void processSynonymToken(PQLToken& curr);
    void processLastArgument();

public:
    explicit PatternParserState(PQLParserContext& parserContext);
    void handleToken() override;
    ~PatternParserState() override = default;
};
