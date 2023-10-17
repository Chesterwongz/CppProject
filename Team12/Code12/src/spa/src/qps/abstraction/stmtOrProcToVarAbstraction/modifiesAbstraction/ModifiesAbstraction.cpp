#include "ModifiesAbstraction.h"

/**
 * Modifies abstraction:
 * - firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * - secondArg: Synonym OR Identifier OR Wildcard
 */

vector<pair<string, string>> ModifiesAbstraction::getAllStmtVarRelations(
    StmtType stmtType) {
  return pkb.getAllModifiedVariables(stmtType);
}

vector<pair<string, string>> ModifiesAbstraction::getAllProcVarRelations() {
  return pkb.getModifiesProcPairs();
}

vector<string> ModifiesAbstraction::getStmtsRelatedToVar(const string& varName,
                                                         StmtType stmtType) {
  return pkb.getStatementsModifying(varName, stmtType);
}

vector<string> ModifiesAbstraction::getProcsRelatedToVar(
    const string& varName) {
  return pkb.getProcModifying(varName);
}

vector<pair<string, string>> ModifiesAbstraction::getVarsRelatedToStmt(
    int stmtNum, StmtType stmtType) {
  return pkb.getVariablesModifiedBy(stmtNum, stmtType);
}

vector<string> ModifiesAbstraction::getVarsRelatedToProc(
    const string& procName) {
  return pkb.getVarsModifiedByProc(procName);
}

bool ModifiesAbstraction::isVarRelatedToStmt(const string& varName,
                                             const string& stmtNum) {
  return pkb.isVariableModifiedBy(varName, stmtNum);
}

bool ModifiesAbstraction::isVarRelatedToProc(const string& procName,
                                             const string& varName) {
  return pkb.isVariableModifiedByProc(procName, varName);
}
