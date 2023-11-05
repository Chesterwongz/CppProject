#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/common/Keywords.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/withEvaluator/WithEvaluator.h"

using std::unique_ptr, std::string, std::move, std::pair, std::make_pair,
    std::function, std::make_unique;

typedef function<IntermediateTable()> EntityValueFunc;

class SingleSynWithEvaluator : public WithEvaluator {
 protected:
  SynonymArg& synonymArg;
  AbstractArgument& valueArg;

  IntermediateTable getCallValueArgResult();
  IntermediateTable getReadValueArgResult();
  IntermediateTable getPrintValueArgResult();
  IntermediateTable getStmtValueArgResult();
  IntermediateTable getVarValueArgResult();
  IntermediateTable getConstantValueArgResult();
  IntermediateTable getProcValueArgResult();

  unordered_map<Entity, EntityValueFunc> valueArgResultFuncMap = {
      {CALL_ENTITY, [this]() { return getCallValueArgResult(); }},
      {READ_ENTITY, [this]() { return getReadValueArgResult(); }},
      {PRINT_ENTITY, [this]() { return getPrintValueArgResult(); }},
      {STMT_ENTITY, [this]() { return getStmtValueArgResult(); }},
      {ASSIGN_ENTITY, [this]() { return getStmtValueArgResult(); }},
      {IF_ENTITY, [this]() { return getStmtValueArgResult(); }},
      {WHILE_ENTITY, [this]() { return getStmtValueArgResult(); }},
      {VARIABLE_ENTITY, [this]() { return getVarValueArgResult(); }},
      {CONSTANT_ENTITY, [this]() { return getConstantValueArgResult(); }},
      {PROCEDURE_ENTITY, [this]() { return getProcValueArgResult(); }}};

 public:
  explicit SingleSynWithEvaluator(SynonymArg& firstArg,
                                  AbstractArgument& secondArg,
                                  PKBReader& pkbReader)
      : WithEvaluator(pkbReader),
        synonymArg(firstArg),
        valueArg(secondArg) {}

  IntermediateTable evaluate() override;
};
