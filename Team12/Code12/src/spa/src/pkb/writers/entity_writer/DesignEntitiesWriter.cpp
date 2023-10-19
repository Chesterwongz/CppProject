#include "DesignEntitiesWriter.h"

void DesignEntitiesWriter::addVar(const std::string& varName) {
  entityStore.addVar(varName);
}

void DesignEntitiesWriter::addConst(const std::string& constValue) {
  entityStore.addConst(constValue);
}

void DesignEntitiesWriter::addProc(const std::string& procName) {
  entityStore.addProc(procName);
}

void DesignEntitiesWriter::addStmt(int stmtNum, StmtType stmtType) {
  stmtStore.addStmt(stmtNum, stmtType);
}
