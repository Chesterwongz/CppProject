#include "SynonymResFactory.h"

SynonymRes& SynonymResFactory::getSynonymResRef(
    unordered_map<AttrRef, string> attrRefMap) {
  string key = SynonymResUtils::buildKey(attrRefMap);
  if (SynonymRes::SYNONYM_RES_POOL.find(key) ==
      SynonymRes::SYNONYM_RES_POOL.end()) {
    // insert synonymRes into pool if it doesn't exist
    SynonymRes::SYNONYM_RES_POOL.insert(
        {{key, SynonymRes(std::move(attrRefMap))}});
  }
  // return ref of object in pool
  return SynonymRes::SYNONYM_RES_POOL.at(key);
}

SynonymRes& SynonymResFactory::buildDefaultSynonym(const string& value) {
  unordered_map<AttrRef, string> attrRefMap {
      {ATTR_REF_DEFAULT, value},
  };
  return getSynonymResRef(std::move(attrRefMap));
}

SynonymRes& SynonymResFactory::buildCallsSynonym(const string& stmtNumber,
                                                 const string& procName) {
  unordered_map<AttrRef, string> attrRefMap {
      {ATTR_REF_DEFAULT, stmtNumber},
      {ATTR_REF_STMT_NUMBER, stmtNumber},
      {ATTR_REF_PROC_NAME, procName},
  };
  return getSynonymResRef(std::move(attrRefMap));
}

SynonymRes& SynonymResFactory::buildConstantSynonym(const string& value) {
  unordered_map<AttrRef, string> attrRefMap {
      {ATTR_REF_DEFAULT, value},
      {ATTR_REF_VALUE, value},
  };
  return getSynonymResRef(std::move(attrRefMap));
}

SynonymRes& SynonymResFactory::buildPrintSynonym(const string& stmtNumber,
                                                 const string& varName) {
  unordered_map<AttrRef, string> attrRefMap {
      {ATTR_REF_DEFAULT, stmtNumber},
      {ATTR_REF_STMT_NUMBER, stmtNumber},
      {ATTR_REF_VAR_NAME, varName},
  };
  return getSynonymResRef(std::move(attrRefMap));
}

SynonymRes& SynonymResFactory::buildProcSynonym(const string& procName) {
  SynonymRes synonymRes = SynonymRes(procName);
  synonymRes.attributeMap[ATTR_REF_PROC_NAME] = procName;
  unordered_map<AttrRef, string> attrRefMap {
      {ATTR_REF_DEFAULT, procName},
      {ATTR_REF_PROC_NAME, procName},
  };
  return getSynonymResRef(std::move(attrRefMap));
}

SynonymRes& SynonymResFactory::buildReadSynonym(const string& stmtNumber,
                                                const string& varName) {
  unordered_map<AttrRef, string> attrRefMap {
      {ATTR_REF_DEFAULT, stmtNumber},
      {ATTR_REF_STMT_NUMBER, stmtNumber},
      {ATTR_REF_VAR_NAME, varName},
  };
  return getSynonymResRef(std::move(attrRefMap));
}

SynonymRes& SynonymResFactory::buildStmtSynonym(const string& stmtNumber) {
  unordered_map<AttrRef, string> attrRefMap {
      {ATTR_REF_DEFAULT, stmtNumber},
      {ATTR_REF_STMT_NUMBER, stmtNumber},
  };
  return getSynonymResRef(std::move(attrRefMap));
}

SynonymRes& SynonymResFactory::buildVarSynonym(const string& varName) {
  unordered_map<AttrRef, string> attrRefMap {
      {ATTR_REF_DEFAULT, varName},
      {ATTR_REF_VAR_NAME, varName},
  };
  return getSynonymResRef(std::move(attrRefMap));
}
