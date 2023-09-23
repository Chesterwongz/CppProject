#pragma once

#include "qps/parser/IParserState.h"
#include "qps/argument/IArgument.h"

class RelationshipParserState : public IParserState {
protected:
    bool isInBracket;
    vector<IArgument> arguments;
    bool isSafeExit(size_t expectedArgs, size_t actualArgs);
    explicit RelationshipParserState(bool isInBracket);
    void processNameToken(PQLToken &curr) override;

public:
    ~RelationshipParserState() override = default;
};
