#include "SuchThatClause.h"

#include "qps/abstraction/AbstractionFactory.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/clause/utils/ClauseUtil.h"

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
set<string> SuchThatClause::getClauseSynonyms() {
  return ClauseUtil::getSynonymArgValues(this->firstArg, this->secondArg);
}

string SuchThatClause::getKey() {
  return AbstractionEnumToStringMap.at(this->relationship) + "|" +
         this->firstArg->getValue() + "|" + this->secondArg->getValue();
}
