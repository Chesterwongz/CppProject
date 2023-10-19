#include "ModifiesAbstraction.h"

/**
 * Modifies abstraction:
 * - firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * - secondArg: Synonym OR Identifier OR Wildcard
 */

vector<pair<string, string>> ModifiesAbstraction::getAllStmtVarRelations(
    StmtType stmtType) {
  return pkb.getModifiesStmtPairs(stmtType);
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

vector<string> ModifiesAbstraction::getVarsRelatedToStmt(
    int firstArgStmtNumber) {
  return pkb.getVariablesModifiedBy(firstArgStmtNumber);
}

vector<string> ModifiesAbstraction::getVarsRelatedToProc(
    const string& procName) {
  return pkb.getVarsModifiedByProc(procName);
}

bool ModifiesAbstraction::isVarRelatedToStmt(int stmtNum,
                                             const string& varName) {
  return pkb.isVariableModifiedBy(stmtNum, varName);
}

bool ModifiesAbstraction::isVarRelatedToProc(const string& procName,
                                             const string& varName) {
  return pkb.isVariableModifiedByProc(procName, varName);
}
