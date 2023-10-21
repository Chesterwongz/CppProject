#include "UsesAbstraction.h"

/**
 * Uses abstraction:
 * - firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * - secondArg: Synonym OR Identifier OR Wildcard
 */

bool UsesAbstraction::isFirstSynonymInvalid() {
  return !this->firstArg.isProcSynonym() &&
         this->getFirstArgStmtType() == StmtType::READ;
}

vector<pair<string, string>> UsesAbstraction::getAllStmtVarRelations(
    StmtType stmtType) {
  return pkb.getUsesStmtPairs(stmtType);
}

vector<pair<string, string>> UsesAbstraction::getAllProcVarRelations() {
  return pkb.getUsesProcPairs();
}

vector<string> UsesAbstraction::getStmtsRelatedToVar(const string& varName,
                                                     StmtType stmtType) {
  return pkb.getStatementsUsing(varName, stmtType);
}

vector<string> UsesAbstraction::getProcsRelatedToVar(const string& varName) {
  return pkb.getProcUsing(varName);
}

vector<string> UsesAbstraction::getVarsRelatedToStmt(int stmtNum) {
  return pkb.getVariablesUsedBy(stmtNum);
}

vector<string> UsesAbstraction::getVarsRelatedToProc(const string& procName) {
  return pkb.getVarsUsedByProc(procName);
}

bool UsesAbstraction::isVarRelatedToStmt(int stmtNum, const string& varName) {
  return pkb.isVariableUsedBy(stmtNum, varName);
}

bool UsesAbstraction::isVarRelatedToProc(const string& procName,
                                         const string& varName) {
  return pkb.isVariableUsedByProc(procName, varName);
}
