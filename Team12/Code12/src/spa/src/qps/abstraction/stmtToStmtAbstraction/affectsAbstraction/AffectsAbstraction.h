#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/stmtToStmtAbstraction/StmtToStmtAbstraction.h"

class AffectsAbstraction : public StmtToStmtAbstraction {
 private:
  static bool isInvalidStmtType(StmtType stmtType);

  bool isFirstSynonymInvalid() override;

  bool isSecondSynonymInvalid() override;

  bool isSelfReferencePossible() override;

  vector<pair<string, string>> getAllPairs(StmtType firstStmtType,
                                           StmtType secondStmtType) override;
  vector<string> getFirstStmt(int secondStmtNumber,
                              StmtType firstStmtType) override;
  vector<string> getSecondStmt(int firstStmtNumber,
                               StmtType secondStmtType) override;
  bool isStmtRelatedToStmt(int stmtNum1, int stmtNum2) override;

 public:
  explicit AffectsAbstraction(AbstractionParams &abstractionParams)
      : StmtToStmtAbstraction(abstractionParams) {}
};
