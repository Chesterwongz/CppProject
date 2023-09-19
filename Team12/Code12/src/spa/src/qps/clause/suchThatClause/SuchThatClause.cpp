#include "SuchThatClause.h"
#include "qps/abstraction/IAbstraction.h"
#include "qps/abstraction/AbstractionFactory.h"
#include "../../argument/IArgument.h"

SuchThatClause::SuchThatClause (
        Abstraction &relationship,
        unique_ptr<IArgument> &firstArg,
        unique_ptr<IArgument> &secondArg,
        bool isTransitive) :
        relationship(relationship),
        firstArg(std::move(firstArg)),
        secondArg(std::move(secondArg)) {
    this->isTransitive = isTransitive;
};

IntermediateTable SuchThatClause::evaluate(
        Context context,
        PKBReader *pkb,
        string &synonymToQuery) {
    AbstractionParams *abstractionParams = {};

    abstractionParams->abstraction = this->relationship;
    abstractionParams->pkb = pkb;
    abstractionParams->context = std::move(context);
    abstractionParams->firstArg = *(this->firstArg);
    abstractionParams->secondArg = *(this->secondArg);
    abstractionParams->isTransitive = this->isTransitive;

    std::unique_ptr<IAbstraction> executableAbstraction =
            AbstractionFactory::createAbstraction(abstractionParams);

    return executableAbstraction->getAbstractions();
}
