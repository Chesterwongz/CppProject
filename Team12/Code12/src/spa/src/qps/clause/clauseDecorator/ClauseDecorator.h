#pragma once

#include <memory>

#include "qps/clause/Clause.h"

using std::unique_ptr;

class ClauseDecorator : public Clause {
 protected:
  unique_ptr<Clause> wrapeeClause;

 public:
  explicit ClauseDecorator(unique_ptr<Clause> wrapeeClause)
      : wrapeeClause(std::move(wrapeeClause)) {}

  vector<unique_ptr<AbstractArgument>> getAllArguments() override;
};
