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
  unique_ptr<SynonymArg> synonymArg;
  unique_ptr<AbstractArgument> valueArg;

  IntermediateTable getValueArgResultCall();
  IntermediateTable getValueArgResultRead();
  IntermediateTable getValueArgResultPrint();
  IntermediateTable getValueArgResultStmt();
  IntermediateTable getValueArgResultVar();
  IntermediateTable getValueArgResultConstant();
  IntermediateTable getValueArgResultProc();

  unordered_map<Entity, EntityValueFunc> valueArgResultFuncMap = {
      {CALL_ENTITY, [this]() { return getValueArgResultCall(); }},
      {READ_ENTITY, [this]() { return getValueArgResultRead(); }},
      {PRINT_ENTITY, [this]() { return getValueArgResultPrint(); }},
      {STMT_ENTITY, [this]() { return getValueArgResultStmt(); }},
      {ASSIGN_ENTITY, [this]() { return getValueArgResultStmt(); }},
      {IF_ENTITY, [this]() { return getValueArgResultStmt(); }},
      {WHILE_ENTITY, [this]() { return getValueArgResultStmt(); }},
      {VARIABLE_ENTITY, [this]() { return getValueArgResultVar(); }},
      {CONSTANT_ENTITY, [this]() { return getValueArgResultConstant(); }},
      {PROCEDURE_ENTITY, [this]() { return getValueArgResultProc(); }}
  };

 public:
  explicit SingleSynWithEvaluator(unique_ptr<SynonymArg> firstArg,
                                  unique_ptr<AbstractArgument> secondArg, PKBReader& pkbReader)
      : WithEvaluator(pkbReader), synonymArg(move(firstArg)), valueArg(move(secondArg)) {};

  IntermediateTable evaluate() override;
};
