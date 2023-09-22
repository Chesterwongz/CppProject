#include "qps/token/suchThatToken/SuchThatToken.h"
#include "../../argument/argumentFactory/ArgumentFactory.h"
#include "../../clause/suchThatClause/SuchThatClause.h"

using std::string;

SuchThatToken::SuchThatToken(Abstraction relationship, string first, string second) : relationship(relationship) {
    firstArg = ArgumentFactory::createArgument(first);
    secondArg = ArgumentFactory::createArgument(second);
}

const Abstraction SuchThatToken::getRelationship() {
    return relationship;
}

// tbh not sure if returning the pointer directly is even needed
const IArgument* SuchThatToken::getFirstArgument() {
    return firstArg.get();
}

// tbh not sure if returning the pointer directly is even needed
const IArgument* SuchThatToken::getSecondArgument() {
    return secondArg.get();
}

const QPSStringUtils::ArgumentType SuchThatToken::getFirstArgumentType() {
    return firstArg->getArgumentType();
}

const string SuchThatToken::getFirstArgumentValue() {
    return firstArg->getValue();
}

const QPSStringUtils::ArgumentType SuchThatToken::getSecondArgumentType() {
    return secondArg->getArgumentType();
}

const string SuchThatToken::getSecondArgumentValue() {
    return secondArg->getValue();
}

unique_ptr<Clause> SuchThatToken::buildClause() {
    return std::make_unique<SuchThatClause>(this->relationship, firstArg, secondArg);
}

