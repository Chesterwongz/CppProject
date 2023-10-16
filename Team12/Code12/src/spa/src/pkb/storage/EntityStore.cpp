#include "EntityStore.h"

// Setter for variables
void EntityStore::addVar(const std::string& varName) {
  varData.insert(varName);
}

// Setter for constants
void EntityStore::addConst(const std::string& constValue) {
  constData.insert(constValue);
}

// Setter for procedures
void EntityStore::addProc(const std::string& procName) {
  procData.insert(procName);
}

// Get all variables
const std::unordered_set<std::string>& EntityStore::getAllVars() const {
  return varData;
}

// Get all constants
const std::unordered_set<std::string>& EntityStore::getAllConsts() const {
  return constData;
}

// Get all procedures
const std::unordered_set<std::string>& EntityStore::getAllProcs() const {
  return procData;
}
