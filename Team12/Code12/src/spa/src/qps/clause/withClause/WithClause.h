#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "qps/argument/AbstractArgument.h"
#include "qps/clause/Clause.h"
#include "qps/common/Keywords.h"
#include "qps/intermediateTable/IntermediateTable.h"

using std::unique_ptr, std::string, std::move, std::pair, std::make_pair,
    std::function;

class WithClause : public Clause {
 protected:
  unique_ptr<AbstractArgument> firstArg;
  unique_ptr<AbstractArgument> secondArg;

 public:
  explicit WithClause(unique_ptr<AbstractArgument> firstArg,
                      unique_ptr<AbstractArgument> secondArg)
      : firstArg(move(firstArg)), secondArg(move(secondArg)) {}

  IntermediateTable evaluate(PKBReader& pkb) override;
  bool isEquals(const Clause& other) override;
  set<string> getClauseSynonyms() override;
};
