#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "SynonymRes.h"
#include "SynonymResUtils.h"

using std::string, std::unordered_map, std::unique_ptr, std::pair;

class SynonymResFactory {
 private:
  static SynonymRes& getSynonymResRef(
      unordered_map<AttrRef, string> attrRefMap);

 public:
  static SynonymRes& buildDefaultSynonym(const string& value);

  static SynonymRes& buildCallsSynonym(const string& stmtNumber,
                                       const string& procName);

  static SynonymRes& buildConstantSynonym(const string& value);

  static SynonymRes& buildPrintSynonym(const string& stmtNumber,
                                       const string& varName);

  static SynonymRes& buildProcSynonym(const string& procName);

  static SynonymRes& buildReadSynonym(const string& stmtNumber,
                                      const string& varName);

  static SynonymRes& buildStmtSynonym(const string& stmtNumber);

  static SynonymRes& buildVarSynonym(const string& varName);

  static vector<std::reference_wrapper<SynonymRes>> buildStmtSynonymResVector(
      const vector<string>& stmtNums);

  static vector<std::reference_wrapper<SynonymRes>>
  buildConstantSynonymResVector(const vector<string>& stmtNums);

  static vector<std::reference_wrapper<SynonymRes>> buildProcSynonymResVector(
      const vector<string>& stmtNums);

  static vector<std::reference_wrapper<SynonymRes>> buildVarSynonymResVector(
      const vector<string>& stmtNums);

  static vector<std::reference_wrapper<SynonymRes>> buildCallSynonymResVector(
      const vector<pair<string, string>>& callProcNamePairs);

  static vector<std::reference_wrapper<SynonymRes>> buildReadSynonymResVector(
      const vector<pair<string, string>>& callProcNamePairs);

  static vector<std::reference_wrapper<SynonymRes>> buildPrintSynonymResVector(
      const vector<pair<string, string>>& callProcNamePairs);
};
