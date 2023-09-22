#include "SuchThatClause.h"
#include "qps/abstraction/IAbstraction.h"
#include "qps/abstraction/AbstractionFactory.h"
#include "qps/argument/IArgument.h"

SuchThatClause::SuchThatClause (
        Abstraction &relationship,
        unique_ptr<IArgument> &firstArg,
        unique_ptr<IArgument> &secondArg) :
        relationship(relationship),
        firstArg(std::move(firstArg)),
        secondArg(std::move(secondArg)) {};

QueryResult SuchThatClause::evaluate(
        Context context,
        PKBReader& pkb,
        string &synonymToQuery) {
    AbstractionParams abstractionParams = {pkb};

    abstractionParams.abstraction = this->relationship;
    abstractionParams.context = std::move(context);
    abstractionParams.firstArg = firstArg;       // (@yq need to change this)
    abstractionParams.secondArg = secondArg;   //(@yq need to change this)

    std::unique_ptr<IAbstraction> executableAbstraction =
            AbstractionFactory::createAbstraction(abstractionParams);

//    return executableAbstraction-
    return {};
}
