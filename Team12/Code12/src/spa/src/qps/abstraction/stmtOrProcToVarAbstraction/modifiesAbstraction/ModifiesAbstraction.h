#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/stmtOrProcToVarAbstraction/StmtOrProcToVarAbstraction.h"

class ModifiesAbstraction : public StmtOrProcToVarAbstraction {
 private:
  vector<pair<string, string>> getAllStmtVarRelations(
      StmtType stmtType) override;

  vector<pair<string, string>> getAllProcVarRelations() override;

  vector<string> getStmtsRelatedToVar(const string& varName,
                                      StmtType stmtType) override;

  vector<string> getProcsRelatedToVar(const string& varName) override;

  vector<string> getVarsRelatedToStmt(int stmtNum) override;

  vector<string> getVarsRelatedToProc(const string& procName) override;

  bool isVarRelatedToStmt(int stmtNum, const string& varName) override;

  bool isVarRelatedToProc(const string& procName,
                          const string& varName) override;

 public:
  explicit ModifiesAbstraction(AbstractionParams abstractionParams)
      : StmtOrProcToVarAbstraction(abstractionParams){}
};
