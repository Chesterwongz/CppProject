#include "SynonymResFactory.h"

SynonymRes SynonymResFactory::buildDefaultSynonym(const string& value) {
  return SynonymRes(value);
}

SynonymRes SynonymResFactory::buildCallsSynonym(const string& stmtNumber,
                                                string procName) {
  SynonymRes synonymRes = SynonymResFactory::buildStmtSynonym(stmtNumber);
  synonymRes.attributeMap[AttrRef::PROC_NAME_ENUM] = std::move(procName);
  return synonymRes;
}

SynonymRes SynonymResFactory::buildConstantSynonym(const string& value) {
  SynonymRes synonymRes = SynonymRes(value);
  synonymRes.attributeMap[AttrRef::VALUE_ENUM] = value;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildPrintSynonym(const string& stmtNumber,
                                                string varName) {
  SynonymRes synonymRes = SynonymResFactory::buildStmtSynonym(stmtNumber);
  synonymRes.attributeMap[AttrRef::VAR_NAME_ENUM] = std::move(varName);
  return synonymRes;
}

SynonymRes SynonymResFactory::buildProcSynonym(const string& procName) {
  SynonymRes synonymRes = SynonymRes(procName);
  synonymRes.attributeMap[AttrRef::PROC_NAME_ENUM] = procName;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildReadSynonym(const string& stmtNumber,
                                               string varName) {
  SynonymRes synonymRes = SynonymResFactory::buildStmtSynonym(stmtNumber);
  synonymRes.attributeMap[AttrRef::VAR_NAME_ENUM] = std::move(varName);
  return synonymRes;
}

SynonymRes SynonymResFactory::buildStmtSynonym(const string& stmtNumber) {
  SynonymRes synonymRes = SynonymRes(stmtNumber);
  synonymRes.attributeMap[AttrRef::STMT_NUM_ENUM] = stmtNumber;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildVarSynonym(const string& varName) {
  SynonymRes synonymRes = SynonymRes(varName);
  synonymRes.attributeMap[AttrRef::VAR_NAME_ENUM] = varName;
  return synonymRes;
}
