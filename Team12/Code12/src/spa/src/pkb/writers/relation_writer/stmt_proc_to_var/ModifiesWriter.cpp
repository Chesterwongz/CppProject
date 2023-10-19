#include "ModifiesWriter.h"

void ModifiesWriter::addModifies(const std::string& varName, int stmtNum) {
  modifiesStore.addRelation(stmtNum, varName);
}

void ModifiesWriter::addModifies(const std::string& varName,
                                 const std::string& procName) {
  modifiesPStore.addRelation(procName, varName);
}
