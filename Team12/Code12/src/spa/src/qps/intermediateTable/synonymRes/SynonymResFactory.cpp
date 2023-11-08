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

vector<std::reference_wrapper<SynonymRes>>
SynonymResFactory::buildStmtSynonymResVector(const vector<string>& stmtNums) {
  vector<std::reference_wrapper<SynonymRes>> stmtSynonymResObjs;
  stmtSynonymResObjs.reserve(stmtNums.size());
  for (const string& stmtNum : stmtNums) {
    stmtSynonymResObjs.emplace_back(
        SynonymResFactory::buildStmtSynonym(stmtNum));
  }

  return stmtSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
SynonymResFactory::buildConstantSynonymResVector(
    const vector<string>& constantVals) {
  vector<std::reference_wrapper<SynonymRes>> constSynonymResObjs;
  constSynonymResObjs.reserve(constantVals.size());
  for (const string& constantVal : constantVals) {
    constSynonymResObjs.emplace_back(
        SynonymResFactory::buildConstantSynonym(constantVal));
  }

  return constSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
SynonymResFactory::buildProcSynonymResVector(const vector<string>& procNames) {
  vector<std::reference_wrapper<SynonymRes>> procSynonymResObjs;
  procSynonymResObjs.reserve(procNames.size());
  for (const string& procName : procNames) {
    procSynonymResObjs.emplace_back(
        SynonymResFactory::buildProcSynonym(procName));
  }

  return procSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
SynonymResFactory::buildVarSynonymResVector(const vector<string>& varNames) {
  vector<std::reference_wrapper<SynonymRes>> varSynonymResObjs;
  varSynonymResObjs.reserve(varNames.size());
  for (const string& varName : varNames) {
    varSynonymResObjs.emplace_back(SynonymResFactory::buildVarSynonym(varName));
  }

  return varSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
SynonymResFactory::buildCallSynonymResVector(
    const vector<pair<string, string>>& callProcNamePairs) {
  vector<std::reference_wrapper<SynonymRes>> callSynonymResObjs;
  callSynonymResObjs.reserve(callProcNamePairs.size());
  for (const pair<string, string>& callProcNamePair : callProcNamePairs) {
    callSynonymResObjs.emplace_back(SynonymResFactory::buildCallsSynonym(
        callProcNamePair.first, callProcNamePair.second));
  }

  return callSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
SynonymResFactory::buildReadSynonymResVector(
    const vector<pair<string, string>>& readVarNamePairs) {
  vector<std::reference_wrapper<SynonymRes>> readSynonymResObjs;

  readSynonymResObjs.reserve(readVarNamePairs.size());
  for (const auto& [firstVar, secondVar] : readVarNamePairs) {
    readSynonymResObjs.emplace_back(
        SynonymResFactory::buildReadSynonym(firstVar, secondVar));
  }

  return readSynonymResObjs;
}

vector<std::reference_wrapper<SynonymRes>>
SynonymResFactory::buildPrintSynonymResVector(
    const vector<pair<string, string>>& printVarNamePairs) {
  vector<std::reference_wrapper<SynonymRes>> printSynonymResObjs;

  printSynonymResObjs.reserve(printVarNamePairs.size());
  for (const auto& [firstVar, secondVar] : printVarNamePairs) {
    printSynonymResObjs.emplace_back(
        SynonymResFactory::buildReadSynonym(firstVar, secondVar));
  }

  return printSynonymResObjs;
}
