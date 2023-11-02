#include "SynonymResFactory.h"

SynonymRes SynonymResFactory::buildDefaultSynonym(const string& value) {
  return SynonymRes(value);
}

SynonymRes SynonymResFactory::buildCallsSynonym(const string& stmtNumber,
                                                const string& procName) {
  SynonymRes synonymRes = SynonymResFactory::buildStmtSynonym(stmtNumber);
  synonymRes.attributeMap[ATTR_REF_PROC_NAME] = procName;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildConstantSynonym(const string& value) {
  SynonymRes synonymRes = SynonymRes(value);
  synonymRes.attributeMap[ATTR_REF_VALUE] = value;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildPrintSynonym(const string& stmtNumber,
                                                const string& varName) {
  SynonymRes synonymRes = SynonymResFactory::buildStmtSynonym(stmtNumber);
  synonymRes.attributeMap[ATTR_REF_VAR_NAME] = varName;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildProcSynonym(const string& procName) {
  SynonymRes synonymRes = SynonymRes(procName);
  synonymRes.attributeMap[ATTR_REF_PROC_NAME] = procName;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildReadSynonym(const string& stmtNumber,
                                               const string& varName) {
  SynonymRes synonymRes = SynonymResFactory::buildStmtSynonym(stmtNumber);
  synonymRes.attributeMap[ATTR_REF_VAR_NAME] = varName;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildStmtSynonym(const string& stmtNumber) {
  SynonymRes synonymRes = SynonymRes(stmtNumber);
  synonymRes.attributeMap[ATTR_REF_STMT_NUMBER] = stmtNumber;
  return synonymRes;
}

SynonymRes SynonymResFactory::buildVarSynonym(const string& varName) {
  SynonymRes synonymRes = SynonymRes(varName);
  synonymRes.attributeMap[ATTR_REF_VAR_NAME] = varName;
  return synonymRes;
}
