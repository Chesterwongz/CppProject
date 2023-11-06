#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "qps/clause/Clause.h"

using std::unique_ptr, std::vector, std::string, std::set;

class ClauseDecorator : public Clause {
 protected:
  unique_ptr<Clause> wrapeeClause;

 public:
  explicit ClauseDecorator(unique_ptr<Clause> wrapeeClause)
      : wrapeeClause(std::move(wrapeeClause)) {}

  vector<const AbstractArgument*> getAllArguments() override;

  set<string> getClauseSynonyms() override;

  string getKey() override;
};
