#pragma once

#include <string>

#include "qps/token/QueryToken.h"

typedef std::string Abstraction;

class SuchThatToken : public QueryToken {
private:
    Abstraction relationship;
    Reference firstArg;
    Reference secondArg;

public:
    explicit SuchThatToken(Abstraction relationship, Reference first, Reference second);
    const Abstraction getRelationship();
    const Reference getFirstArgument();
    const Reference getSecondArgument();
};