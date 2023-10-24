#pragma once

#include <set>
#include <string>
#include <unordered_map>

#include "common/StmtTypes.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/common/Keywords.h"

using std::string, std::unordered_map, std::set;

namespace ClauseUtil {
static Entity getArgEntity(AbstractArgument& arg) {
  if (arg.isSynonym()) {
    return reinterpret_cast<SynonymArg&>(arg).getEntityType();
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
}  // namespace ClauseUtil
