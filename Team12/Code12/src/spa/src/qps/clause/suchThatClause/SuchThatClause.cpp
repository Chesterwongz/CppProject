#include "SuchThatClause.h"
#include "qps/abstraction/IAbstraction.h"

SuchThatClause::SuchThatClause (
        Abstraction &relationship,
        Reference &firstArg,
        Reference &secondArg) :
        relationship(relationship),
        firstArg(firstArg),
        secondArg(secondArg) {}

std::set<int> SuchThatClause::evaluate(
        Context context,
        PKBReader *pkb) {
    AbstractionParams *abstractionParams = {};
    abstractionParams->abstraction = this->relationship;
    abstractionParams->pkb = pkb;
    abstractionParams->context = context;
    abstractionParams->firstArg = firstArg;
    abstractionParams->secondArg = secondArg;
    AbstractionFactory fac = AbstractionFactory();
    auto executableAbstraction =
            AbstractionFactory::createAbstraction(abstractionParams);
    return executableAbstraction.getAbstractions();
}



