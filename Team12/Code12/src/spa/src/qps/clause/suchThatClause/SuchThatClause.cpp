#include "SuchThatClause.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/AbstractionFactory.h"
#include "qps/argument/AbstractArgument.h"

SuchThatClause::SuchThatClause (
        Abstraction relationship,
        unique_ptr<AbstractArgument> firstArg,
        unique_ptr<AbstractArgument> secondArg) :
        relationship(relationship),
        firstArg(std::move(firstArg)),
        secondArg(std::move(secondArg)) {};

// todo: remove after integration
SuchThatClause::SuchThatClause(
        Abstraction relationship,
        unique_ptr<AbstractArgument> firstArg,
        unique_ptr<AbstractArgument> secondArg,
        bool isTransitive) :
        relationship(relationship),
        firstArg(std::move(firstArg)),
        secondArg(std::move(secondArg)) {
    throw std::runtime_error("invalid constructor used");
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
                    *(this->secondArg)
            );

    std::unique_ptr<BaseAbstraction> executableAbstraction =
            AbstractionFactory::createAbstraction(*abstractionParams);

    return executableAbstraction->evaluate();
}

bool SuchThatClause::isEquals(const Clause& other) {
    const auto* otherSuchThat = dynamic_cast<const SuchThatClause*>(&other);
    if (!otherSuchThat) return false;

    return relationship == otherSuchThat->relationship
    && *firstArg == *otherSuchThat->firstArg
    && *secondArg == *otherSuchThat->secondArg;
}
