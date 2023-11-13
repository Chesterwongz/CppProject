#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "qps/clause/BaseClause.h"
#include "qps/clause/Clause.h"

using std::unique_ptr, std::vector, std::string, std::set;

class ClauseDecorator : public BaseClause {
 protected:
  unique_ptr<Clause> wrapeeClause;

 public:
  explicit ClauseDecorator(unique_ptr<Clause> wrapeeClause)
      : wrapeeClause(std::move(wrapeeClause)) {}

  set<string> getClauseSynonyms() override;

  ClauseKey getKey() override;
};
