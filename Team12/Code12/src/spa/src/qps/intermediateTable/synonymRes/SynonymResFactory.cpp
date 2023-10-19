#include "SynonymResFactory.h"

#include <utility>

SynonymRes SynonymResFactory::buildDefaultSynonym(const string& value) {
  return SynonymRes(value);
}

SynonymRes SynonymResFactory::buildCallsSynonym(const string& stmtNumber,
                                                string procName) {
  SynonymRes synonymRes = SynonymResFactory::buildStmtSynonym(stmtNumber);
  synonymRes.attributeMap[AttrRefEnum::PROC_NAME_ENUM] = std::move(procName);
  return synonymRes;
}

SynonymRes SynonymResFactory::buildConstantSynonym(const string& value) {
  SynonymRes synonymRes = SynonymRes(value);
  synonymRes.attributeMap[AttrRefEnum::VALUE_ENUM] = value;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildPrintSynonym(const string& stmtNumber,
                                                string varName) {
  SynonymRes synonymRes = SynonymResFactory::buildStmtSynonym(stmtNumber);
  synonymRes.attributeMap[AttrRefEnum::VAR_NAME_ENUM] = std::move(varName);
  return synonymRes;
}

SynonymRes SynonymResFactory::buildProcSynonym(const string& procName) {
  SynonymRes synonymRes = SynonymRes(procName);
  synonymRes.attributeMap[AttrRefEnum::PROC_NAME_ENUM] = procName;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildReadSynonym(const string& stmtNumber,
                                               string varName) {
  SynonymRes synonymRes = SynonymResFactory::buildStmtSynonym(stmtNumber);
  synonymRes.attributeMap[AttrRefEnum::VAR_NAME_ENUM] = std::move(varName);
  return synonymRes;
}

SynonymRes SynonymResFactory::buildStmtSynonym(const string& stmtNumber) {
  SynonymRes synonymRes = SynonymRes(stmtNumber);
  synonymRes.attributeMap[AttrRefEnum::STMT_NUM_ENUM] = stmtNumber;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildVarSynonym(const string& varName) {
  SynonymRes synonymRes = SynonymRes(varName);
  synonymRes.attributeMap[AttrRefEnum::VAR_NAME_ENUM] = varName;
  return synonymRes;
}
