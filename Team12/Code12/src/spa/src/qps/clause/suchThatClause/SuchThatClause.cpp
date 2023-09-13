#include "SuchThatClause.h"
#include "qps/abstraction/IAbstraction.h"
#include "qps/abstraction/AbstractionFactory.h"
#include "../../argument/IArgument.h"

SuchThatClause::SuchThatClause (
        Abstraction &relationship,
        IArgument* firstArg,
        IArgument* secondArg) :
        relationship(relationship),
        firstArg(firstArg),
        secondArg(secondArg) {}

std::unordered_set<int> SuchThatClause::evaluate(
        Context context,
        PKBReader *pkb) {
    AbstractionParams *abstractionParams = {};

    abstractionParams->abstraction = this->relationship;
    abstractionParams->pkb = pkb;
    abstractionParams->context = std::move(context);
    abstractionParams->firstArg = firstArg;
    abstractionParams->secondArg = secondArg;

    std::unique_ptr<IAbstraction> executableAbstraction =
            AbstractionFactory::createAbstraction(abstractionParams);

    return executableAbstraction->getAbstractions();
}
