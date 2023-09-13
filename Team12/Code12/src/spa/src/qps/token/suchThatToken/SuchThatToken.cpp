#include "qps/token/suchThatToken/SuchThatToken.h"
#include "../../argument/IArgument.h"
#include "../../argument/argumentFactory/ArgumentFactory.h"
#include "../../clause/Clause.h"
#include "../../clause/suchThatClause/SuchThatClause.h"

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

const string SuchThatToken::getFirstArgumentType() {
    return firstArg->getArgumentType();
}

const string SuchThatToken::getFirstArgumentValue() {
    return firstArg->getValue();
}

const string SuchThatToken::getSecondArgumentType() {
    return secondArg->getArgumentType();
}

const string SuchThatToken::getSecondArgumentValue() {
    return secondArg->getValue();
}

unique_ptr<Clause> SuchThatToken::buildClause() {
    return std::make_unique<SuchThatClause>(this->relationship, firstArg, secondArg);
}

