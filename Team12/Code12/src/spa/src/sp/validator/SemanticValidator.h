#pragma once

#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "sp/ast/ProgramNode.h"
#include "common/ast/TNode.h"
#include "sp/exceptions/CyclicProcCallException.h"
#include "sp/exceptions/DuplicateProcNameException.h"
#include "sp/exceptions/UndefinedProcCallException.h"

class SemanticValidator {
 private:
  std::string callerProc;
  std::unordered_map<std::string, std::unordered_set<std::string>> adjList;
  std::unordered_map<std::string, int> indegree;
  void initialiseGraph(const TNode& root);
  void updateGraph(const std::string& callee);
  bool isProcedureDefined(const std::string& procName);
  bool isDuplicateCall(const string& callee);
  bool hasCyclicCalls();
  void dfs(const TNode& node);

 public:
  SemanticValidator();
  void validate(const TNode& root);
};
