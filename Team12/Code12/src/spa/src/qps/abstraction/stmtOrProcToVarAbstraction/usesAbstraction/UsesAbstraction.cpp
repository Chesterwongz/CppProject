#include "UsesAbstraction.h"

/**
 * Uses abstraction:
 * - firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * - secondArg: Synonym OR Identifier OR Wildcard
 */

vector<pair<string, string>> UsesAbstraction::getAllStmtVarRelations(
    StmtType stmtType) {
  return pkb.getAllUsedVariables(stmtType);
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

vector<pair<string, string>> UsesAbstraction::getVarsRelatedToStmt(
    int stmtNum, StmtType stmtType) {
  return pkb.getVariablesUsedBy(stmtNum, stmtType);
}

vector<string> UsesAbstraction::getVarsRelatedToProc(const string& procName) {
  return pkb.getVarsUsedByProc(procName);
}

bool UsesAbstraction::isVarRelatedToStmt(const string& varName,
                                         const string& stmtNum) {
  return pkb.isVariableUsedBy(varName, stmtNum);
}

bool UsesAbstraction::isVarRelatedToProc(const string& procName,
                                         const string& varName) {
  return pkb.isVariableUsedByProc(procName, varName);
}
