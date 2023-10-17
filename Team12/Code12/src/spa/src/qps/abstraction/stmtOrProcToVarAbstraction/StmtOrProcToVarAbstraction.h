#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/abstraction/AbstractionUtils.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/intermediateTable/IntermediateTable.h"

class StmtOrProcToVarAbstraction : public BaseAbstraction {
 private:
  IntermediateTable handleSynonymOrWildcardArgs();
  IntermediateTable handleProcNameWithVarSynonymOrWildcard();

  /**
   * Abstraction(a, b): get all a, b pairs where a has specified stmtType
   */
  virtual vector<pair<string, string>> getAllStmtVarRelations(
      StmtType stmtType) = 0;

  /**
   * Abstraction(a, b): get all a, b pairs where a has specified procName
   */
  virtual vector<pair<string, string>> getAllProcVarRelations() = 0;

  /**
   * Abstraction(a, b): get all stmt a where a has specified stmtType
   * and b has specified varName
   */
  virtual vector<string> getStmtsRelatedToVar(const string& varName,
                                              StmtType stmtType) = 0;

  /**
   * Abstraction(a, b): get all proc a where b has specified varName
   */
  virtual vector<string> getProcsRelatedToVar(const string& varName) = 0;

  /**
   * Abstraction(a, b): get all a, b pairs where a has specified stmtType
   * and stmtNum
   */
  virtual vector<pair<string, string>> getVarsRelatedToStmt(
      int stmtNum, StmtType stmtType) = 0;

  /**
   * Abstraction(a, b): get all a, b pairs where a has specified procName
   */
  virtual vector<string> getVarsRelatedToProc(const string& procName) = 0;

  /**
   * Abstraction(a, b): check if specified stmtNum and varName are related
   */
  virtual bool isVarRelatedToStmt(const string& varName,
                                  const string& stmtNum) = 0;

  /**
   * Abstraction(a, b): check if specified procName and varName are related
   */
  virtual bool isVarRelatedToProc(const string& procName,
                                  const string& varName) = 0;

 protected:
  explicit StmtOrProcToVarAbstraction(AbstractionParams abstractionParams)
      : BaseAbstraction(abstractionParams) {}

  IntermediateTable evaluateSynonymSynonym() override;
  IntermediateTable evaluateSynonymIdent() override;
  IntermediateTable evaluateSynonymWildcard() override;

  IntermediateTable evaluateIntegerSynonym() override;
  IntermediateTable evaluateIntegerIdent() override;
  IntermediateTable evaluateIntegerWildcard() override;

  IntermediateTable evaluateIdentSynonym() override;
  IntermediateTable evaluateIdentIdent() override;
  IntermediateTable evaluateIdentWildcard() override;
};
