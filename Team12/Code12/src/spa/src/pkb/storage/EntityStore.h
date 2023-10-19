#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/Constants.h"
#include "common/StmtTypes.h"
#include "pkb/utils/PredicateUtils.h"

class EntityStore {
 private:
  std::unordered_set<std::string> varData;

  std::unordered_set<std::string> constData;

  std::unordered_set<std::string> procData;

 public:
  void addVar(const std::string& varName);
  void addConst(const std::string& constValue);
  void addProc(const std::string& procName);
  [[nodiscard]] const std::unordered_set<std::string>& getAllVars() const;
  [[nodiscard]] const std::unordered_set<std::string>& getAllConsts() const;
  [[nodiscard]] const std::unordered_set<std::string>& getAllProcs() const;
  bool hasConst(const std::string& constVal) const;
  bool hasProc(const std::string& procName) const;
  bool hasVariable(const std::string& variableName) const;
};
