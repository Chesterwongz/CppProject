#pragma once

#include <string>
#include <unordered_map>

#include "common/StmtTypes.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/common/Keywords.h"

using std::string, std::unordered_map;

namespace ClauseUtil {
static Entity getArgEntity(AbstractArgument& arg) {
  if (arg.isSynonym()) {
    return reinterpret_cast<SynonymArg&>(arg).getEntityType();
  }
  return INVALID_ENTITY;
}
}  // namespace ClauseUtil
