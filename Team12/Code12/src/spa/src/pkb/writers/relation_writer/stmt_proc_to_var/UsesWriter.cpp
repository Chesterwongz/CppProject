#include "UsesWriter.h"

void UsesWriter::addUses(const std::string& varName, int stmtNum) {
  usesStore.addRelation(stmtNum, varName);
}

void UsesWriter::addUses(const std::string& varName,
                         const std::string& procName) {
  usesPStore.addRelation(procName, varName);
}
