#include "qps/token/suchThatToken/SuchThatToken.h"
#include "../../argument/IArgument.h"
#include "../../argument/argumentFactory/ArgumentFactory.h"

using std::string;

SuchThatToken::SuchThatToken(Abstraction relationship, string first, string second) : relationship(relationship) {
    firstArg = ArgumentFactory::createArgument(first).get();
    secondArg = ArgumentFactory::createArgument(second).get();
}

const Abstraction SuchThatToken::getRelationship() {
    return relationship;
}

const IArgument* SuchThatToken::getFirstArgument() {
    return firstArg;
}

const IArgument* SuchThatToken::getSecondArgument() {
    return secondArg;
}

const IArgument SuchThatToken::getFirstArgumentType() {
    return firstArg->getArgumentType();
}

const IArgument SuchThatToken::getFirstArgumentValue() {
    return firstArg->getValue();
}

const IArgument SuchThatToken::getSecondArgumentType() {
    return secondArg->getArgumentType();
}

const IArgument SuchThatToken::getSecondArgumentType() {
    return secondArg->getValue();
}

unique_ptr<Clause> SuchThatToken::buildClause() {
    // placeholder
    return nullptr;
}

