#include "SuchThatClause.h"

#include <vector>

#include "qps/abstraction/AbstractionFactory.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/argument/AbstractArgument.h"

vector<const AbstractArgument*> SuchThatClause::getAllArguments() {
  vector<const AbstractArgument*> argVector;

  argVector.push_back(firstArg.get());
  argVector.push_back(secondArg.get());

  return argVector;
}

SuchThatClause::SuchThatClause(Abstraction relationship,
                               unique_ptr<AbstractArgument> firstArg,
                               unique_ptr<AbstractArgument> secondArg)
    : relationship(relationship),
      firstArg(std::move(firstArg)),
      secondArg(std::move(secondArg)) {}

IntermediateTable SuchThatClause::evaluate(PKBReader& pkb) {
  unique_ptr<AbstractionParams> abstractionParams =
      std::make_unique<AbstractionParams>(
          pkb, this->relationship, *(this->firstArg), *(this->secondArg));

  std::unique_ptr<BaseAbstraction> executableAbstraction =
      AbstractionFactory::createAbstraction(*abstractionParams);

  return executableAbstraction->evaluate();
}

bool SuchThatClause::isEquals(const Clause& other) {
  const auto* otherSuchThat = dynamic_cast<const SuchThatClause*>(&other);
  if (!otherSuchThat) return false;

  return relationship == otherSuchThat->relationship &&
         *firstArg == *otherSuchThat->firstArg &&
         *secondArg == *otherSuchThat->secondArg;
}
