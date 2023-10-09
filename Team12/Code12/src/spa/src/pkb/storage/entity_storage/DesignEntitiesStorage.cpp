#include "DesignEntitiesStorage.h"

// Setter for variables
void DesignEntitiesStorage::setVariable(const std::string& variableName) {
  variableData.insert(variableName);
}

// Setter for constants
void DesignEntitiesStorage::setConstant(const std::string& constantValue) {
  constantData.insert(constantValue);
}

// Setter for procedures
void DesignEntitiesStorage::setProcForStmt(const std::string& procName,
                                           int stmt) {
  stmtToProcMap[stmt] = procName;
  if (procedureData.find(procName) == procedureData.end()) {
    procedureData.insert(procName);
  }
}

// Get all variables
std::set<std::string> DesignEntitiesStorage::getAllVariables() {
  return variableData;
}

// Get all constants
std::set<std::string> DesignEntitiesStorage::getAllConstants() {
  return constantData;
}

// Get all procedures
std::set<std::string> DesignEntitiesStorage::getAllProcedures() {
  return procedureData;
}

std::string DesignEntitiesStorage::getProcFromStmt(int stmtNum) {
  if (stmtToProcMap.find(stmtNum) != stmtToProcMap.end()) {
    return stmtToProcMap[stmtNum];
  }
  return "";
}
