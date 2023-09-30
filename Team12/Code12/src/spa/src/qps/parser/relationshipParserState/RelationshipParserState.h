#pragma once

#include "qps/parser/IParserState.h"
#include "qps/argument/AbstractArgument.h"

class RelationshipParserState : public IParserState {
protected:
    bool isInBracket;
    vector<unique_ptr<AbstractArgument>> arguments;
    void checkSafeExit(size_t expectedArgs, size_t actualArgs);
    explicit RelationshipParserState(bool isInBracket);
    void processNameToken(PQLToken &curr) override;

public:
    ~RelationshipParserState() override = default;
};
