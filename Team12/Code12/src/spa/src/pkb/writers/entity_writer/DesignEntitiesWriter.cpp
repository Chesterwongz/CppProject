#include "DesignEntitiesWriter.h"

void DesignEntitiesWriter::addVariable(const std::string& varName) {
  entityStorage.setVariable(varName);
}

void DesignEntitiesWriter::addConstant(const std::string& constantValue) {
  entityStorage.setConstant(constantValue);
}
void DesignEntitiesWriter::addProcForStmt(const std::string& procName,
                                          int stmtNum) {
  entityStorage.setProcForStmt(procName, stmtNum);
}

void DesignEntitiesWriter::addStmt(int stmtNum, StmtType stmtType) {
  stmtStore.addStmt(stmtNum, stmtType);
}
