#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/StmtToStmtAbstraction.h"

class NextStarAbstraction : public StmtToStmtAbstraction {
 private:
  bool hasPairs() override;

  vector<pair<string, string>> getAllPairs(StmtType firstStmtType,
                                           StmtType secondStmtType) override;
  vector<string> getFirstStmt(int secondStmtNumber,
                              StmtType firstStmtType) override;
  vector<string> getSecondStmt(int firstStmtNumber,
                               StmtType secondStmtType) override;
  bool isStmtRelatedToStmt(int stmtNum1, int stmtNum2) override;

  bool isSelfReferencePossible() override;

 public:
  explicit NextStarAbstraction(AbstractionParams &abstractionParams)
      : StmtToStmtAbstraction(abstractionParams) {}
};
