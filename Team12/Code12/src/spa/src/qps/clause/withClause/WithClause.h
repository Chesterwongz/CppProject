#pragma once

#include <functional>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "qps/argument/AbstractArgument.h"
#include "qps/clause/Clause.h"
#include "qps/clause/utils/ClauseUtil.h"
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
      : firstArg(std::move(firstArg)), secondArg(std::move(secondArg)) {}

  IntermediateTable evaluate(PKBReader& pkb) override;
  bool isEquals(const IClause& other) override;
  vector<const AbstractArgument*> getAllArguments() override;
  set<string> getClauseSynonyms() override;
  string getKey() override;
};
