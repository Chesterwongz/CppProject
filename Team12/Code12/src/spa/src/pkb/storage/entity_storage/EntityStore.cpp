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

// Return true if the particular constant exists
bool EntityStore::hasConst(const std::string& constVal) const {
  return constData.count(constVal);
}

// Return true if the particular procedure exists
bool EntityStore::hasProc(const std::string& procName) const {
  return procData.count(procName);
}

// Return true if the particular variable exists
bool EntityStore::hasVar(const std::string& varName) const {
  return varData.count(varName);
}
