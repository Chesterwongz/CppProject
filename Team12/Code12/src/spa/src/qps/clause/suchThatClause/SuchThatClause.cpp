#include "SuchThatClause.h"
#include "qps/abstraction/BaseAbstraction.h"
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
        PKBReader& pkb) {
    unique_ptr<AbstractionParams> abstractionParams
            = std::make_unique<AbstractionParams>(
                    pkb,
                    context,
                    this->relationship,
                    *(this->firstArg),
                    *(this->secondArg),
                    this->isTransitive
            );

    std::unique_ptr<BaseAbstraction> executableAbstraction =
            AbstractionFactory::createAbstraction(*abstractionParams);

    return AbstractionEvaluator::evaluate(*executableAbstraction);
}

bool SuchThatClause::isEquals(const Clause& other) {
    const auto* otherSuchThat = dynamic_cast<const SuchThatClause*>(&other);
    if (!otherSuchThat) return false;

    return relationship == otherSuchThat->relationship
    && *firstArg == *otherSuchThat->firstArg
    && *secondArg == *otherSuchThat->secondArg
    && isTransitive == otherSuchThat->isTransitive;
}
