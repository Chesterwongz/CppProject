#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/StmtTypes.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/clauseDecorator/notDecorator/NotDecorator.h"
#include "qps/common/Keywords.h"

using std::string, std::unordered_map, std::set, std::reference_wrapper,
    std::vector;

class Clause;
namespace ClauseUtil {
typedef vector<unique_ptr<Clause>> ClauseList;
typedef vector<unique_ptr<NotDecorator>> NotClauseList;

typedef vector<reference_wrapper<unique_ptr<Clause>>> ClauseRefList;

static Entity getArgEntity(AbstractArgument& arg) {
  if (arg.isSynonym()) {
    return dynamic_cast<SynonymArg&>(arg).getEntityType();
  }
  return INVALID_ENTITY;
}

static set<string> getSynonymArgValues(unique_ptr<AbstractArgument>& arg1,
                                       unique_ptr<AbstractArgument>& arg2) {
  set<string> res = {};
  if (arg1->isSynonym()) {
    res.insert(arg1->getValue());
  }
  if (arg2->isSynonym()) {
    res.insert(arg2->getValue());
  }
  return res;
}

const string KEY_DELIMITER = "|";
}  // namespace ClauseUtil
