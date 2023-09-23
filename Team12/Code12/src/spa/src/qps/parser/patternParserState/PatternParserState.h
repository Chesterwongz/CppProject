#pragma once

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/IParserState.h"

using std::make_unique, std::unique_ptr;

class PatternParserState : public IParserState {
private:
    PQLParserContext& parserContext;
    PQLTokenStream& tokenStream;
    PQLTokenType prev;
    bool isInBracket;
    bool isPartialMatch;
    string matchPattern;
    string outerSynonym;
    static PredictiveMap predictiveMap;
    static PQLTokenType exitToken;
    static size_t maxNumberOfArgs;
    int argumentCount;
    // vector of arguments
    void processNameToken(PQLToken& curr) override;
    void processSynonymToken(PQLToken& curr);
    void addAsArgument(PQLToken& curr);

public:
    explicit PatternParserState(PQLParserContext& parserContext);
    void handleToken() override;
    ~PatternParserState() override = default;
};
