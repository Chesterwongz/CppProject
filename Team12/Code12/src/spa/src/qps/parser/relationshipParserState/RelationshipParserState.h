#pragma once

#include "qps/parser/IParserState.h"
#include "qps/argument/IArgument.h"

class RelationshipParserState : public IParserState {
protected:
    bool isInBracket;
    vector<unique_ptr<IArgument>> arguments;
    void checkSafeExit(size_t expectedArgs, size_t actualArgs);
    explicit RelationshipParserState(bool isInBracket);
    void processNameToken(PQLToken &curr) override;

public:
    ~RelationshipParserState() override = default;
};
