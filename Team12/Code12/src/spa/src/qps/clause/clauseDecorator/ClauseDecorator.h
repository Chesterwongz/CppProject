#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "qps/clause/Clause.h"
#include "qps/clause/IClause.h"

using std::unique_ptr, std::vector, std::string, std::set;

class ClauseDecorator : public IClause {
 protected:
  unique_ptr<Clause> wrapeeClause;

 public:
  explicit ClauseDecorator(unique_ptr<Clause> wrapeeClause)
      : wrapeeClause(std::move(wrapeeClause)) {}

  set<string> getClauseSynonyms() override;

  string getKey() override;
};
