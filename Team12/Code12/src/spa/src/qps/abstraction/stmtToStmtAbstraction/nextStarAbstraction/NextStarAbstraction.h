#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/StmtToStmtAbstraction.h"

class NextStarAbstraction : public StmtToStmtAbstraction {
 private:
  vector<pair<string, string>> getAllPairs(StmtType firstStmtType,
                                           StmtType secondStmtType) override;
  vector<string> getFirstStmt(StmtType firstStmtType, int s1) override;
  vector<string> getSecondStmt(StmtType secondStmtType, int s1) override;
  bool isStmtRelatedToStmt(int stmtNum1, int stmtNum2) override;

  bool isSelfReferencePossible() override;

 public:
  explicit NextStarAbstraction(AbstractionParams &abstractionParams)
      : StmtToStmtAbstraction(abstractionParams) {}
};
