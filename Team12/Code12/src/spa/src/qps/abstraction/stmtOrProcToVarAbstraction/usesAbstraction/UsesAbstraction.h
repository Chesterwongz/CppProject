#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/stmtOrProcToVarAbstraction/StmtOrProcToVarAbstraction.h"

class UsesAbstraction : public StmtOrProcToVarAbstraction {
 private:
  vector<pair<string, string>> getAllStmtVarRelations(
      StmtType stmtType) override;

  vector<pair<string, string>> getAllProcVarRelations() override;

  vector<string> getStmtsRelatedToVar(const string& varName,
                                      StmtType stmtType) override;

  vector<string> getProcsRelatedToVar(const string& varName) override;

  vector<pair<string, string>> getVarsRelatedToStmt(int stmtNum,
                                                    StmtType stmtType) override;

  vector<string> getVarsRelatedToProc(const string& procName) override;

  bool isVarRelatedToStmt(const string& varName,
                          const string& stmtNum) override;

  bool isVarRelatedToProc(const string& procName,
                          const string& varName) override;

 public:
  explicit UsesAbstraction(AbstractionParams abstractionParams)
      : StmtOrProcToVarAbstraction(abstractionParams) {}
};
