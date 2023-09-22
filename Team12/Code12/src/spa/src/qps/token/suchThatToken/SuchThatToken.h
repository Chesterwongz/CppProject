#pragma once

#include <string>
#include <memory>

#include "qps/token/QueryToken.h"
#include "../../argument/IArgument.h"
using std::unique_ptr;

using std::string;

typedef std::string Abstraction;

class SuchThatToken : public QueryToken {
private:
    Abstraction relationship;
    unique_ptr<IArgument> firstArg;
    unique_ptr<IArgument> secondArg;

public:
    explicit SuchThatToken(Abstraction relationship, string first, string second);
    const Abstraction getRelationship();
    const IArgument* getFirstArgument();
    const IArgument* getSecondArgument();
    const QPSStringUtils::ArgumentType getFirstArgumentType();
    const string getFirstArgumentValue();
    const QPSStringUtils::ArgumentType getSecondArgumentType();
    const string getSecondArgumentValue();
    unique_ptr<Clause> buildClause();
};