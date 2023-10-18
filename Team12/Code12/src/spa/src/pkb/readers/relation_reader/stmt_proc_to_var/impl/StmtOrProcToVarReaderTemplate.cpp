#include "StmtOrProcToVarReaderTemplate.h"

std::vector<std::string>
StmtOrProcToVarReaderTemplate::getStmtsRelatedToVarByStmtType(
    const std::string& varName, StmtType stmtType) {
  std::vector<std::string> result;


  return result;
}
std::vector<std::pair<std::string, std::string>>
StmtOrProcToVarReaderTemplate::getVarsRelatedToStmtByStmtType(
    int stmtNum, StmtType stmtType) {
  std::vector<std::pair<std::string, std::string>> result;

  std::set<std::string> variables = getVarsRelatedToStmt(stmtNum);

  for (const std::string& v : variables) {
    result.emplace_back(std::to_string(stmtNum), v);
  }

  return result;
}
bool StmtOrProcToVarReaderTemplate::isVarRelatedToStmt(
    const std::string& varName, const std::string& stmtNumStr) {
  std::vector<std::string> allStatementsModifying =
      getStmtsRelatedToVarByStmtType(varName, StmtType::STMT);
  return std::find(allStatementsModifying.begin(), allStatementsModifying.end(),
                   stmtNumStr) != allStatementsModifying.end();
}

std::vector<std::pair<std::string, std::string>>
StmtOrProcToVarReaderTemplate::getAllRelationsByStmtType(
    StmtType statementType) {
  std::vector<std::pair<std::string, std::string>> result;
  return result;
}

bool StmtOrProcToVarReaderTemplate::isVarRelatedToProc(
    const std::string& varName, const std::string& procName) {
  std::unordered_set<std::string> allVarRelated =
      getVarsRelatedToProc(procName);
  return allVarRelated.find(varName) != allVarRelated.end();
}

std::vector<std::pair<std::string, std::string>>
StmtOrProcToVarReaderTemplate::getAllProcRelations() {
  std::vector<std::pair<std::string, std::string>> result;

  std::set<std::string> variables = entity_storage_.getAllVariables();

  for (const std::string& v : variables) {
    std::unordered_set<std::string> procNames = getProcsRelatedToVar(v);

    for (const std::string& procName : procNames) {
      result.emplace_back(procName, v);
    }
  }

  return result;
}

