#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/StmtToStmtAbstraction.h"

class NextAbstraction : public StmtToStmtAbstraction {
 private:
  vector<pair<string, string>> getAllPairs(StmtType firstStmtType,
                                           StmtType secondStmtType) override;
  vector<string> getFirstStmt(int s2, StmtType firstStmtType) override;
  vector<string> getSecondStmt(int s1, StmtType secondStmtType) override;
  bool isStmtRelatedToStmt(int stmtNum1, int stmtNum2) override;

 public:
  explicit NextAbstraction(AbstractionParams &abstractionParams)
      : StmtToStmtAbstraction(abstractionParams) {}
};
