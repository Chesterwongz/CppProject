#include "SuchThatClause.h"
#include "qps/abstraction/IAbstraction.h"
#include "qps/abstraction/AbstractionFactory.h"
#include "qps/argument/IArgument.h"

SuchThatClause::SuchThatClause (
        Abstraction relationship,
        unique_ptr<IArgument> firstArg,
        unique_ptr<IArgument> secondArg,
        bool isTransitive) :
        relationship(relationship),
        firstArg(std::move(firstArg)),
        secondArg(std::move(secondArg)) {
    this->isTransitive = isTransitive;
};

IntermediateTable SuchThatClause::evaluate(
        Context& context,
        PKBReader &pkb) {
    unique_ptr<AbstractionParams> abstractionParams
            = std::make_unique<AbstractionParams>(
                    pkb,
                    std::move(context),
                    this->relationship,
                    *(this->firstArg),
                    *(this->secondArg),
                    this->isTransitive
            );

    std::unique_ptr<IAbstraction> executableAbstraction =
            AbstractionFactory::createAbstraction(*abstractionParams);

    return executableAbstraction->getAbstractions();
}

bool SuchThatClause::isEquals(const SuchThatClause& other) {
    return relationship == other.relationship
    && firstArg == other.firstArg
    && secondArg == other.secondArg
    && isTransitive == other.isTransitive;
}
