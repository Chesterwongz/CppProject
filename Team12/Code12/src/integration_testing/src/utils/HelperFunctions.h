#pragma once

#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/AliasTypes.h"
#include "pkb/facade/PKBReader.h"

using std::string, std::unordered_set, std::set, std::vector;

class HelperFunctions {
 private:
  // TODO(Xiaoyun): remove print methods after MS2 testing
  static void printEntities(const string& abstraction,
                            const unordered_set<string>& set);

 public:
  static bool validateEntities(PKBReader& reader,
                               const set<string>& expectedVars,
                               const set<string>& expectedConstants,
                               const set<string>& expectedProcedures,
                               const set<string>& expectedReadStmts,
                               const set<string>& expectedPrintStmts,
                               const set<string>& expectedAssignStmts,
                               const set<string>& expectedCallStmts,
                               const set<string>& expectedWhileStmts,
                               const set<string>& expectedIfStmts);

  static bool validateFollows(PKBReader& reader,
                              StrStrPairSet& expectedFollowsPairs,
                              StrStrPairSet& expectedFollowsTPairs);

  static bool validateParents(PKBReader& reader,
                              StrStrPairSet& expectedParentChildPairs,
                              StrStrPairSet& expectedParentChildTPairs);

  static bool validateModifies(PKBReader& reader,
                               StrStrPairSet& expectedModifiesPairs);

  static bool validateUses(PKBReader& reader, StrStrPairSet& expectedUsesPairs);

  static bool isAssignResultMatch(vector<pair<string, string>> actual,
                                  StrStrPairSet expected);

  static bool validateModifiesProcVar(PKBReader& reader,
                                      const vector<string>& procs,
                                      ProcToStrSetMap expectedModifiesMap);

  static bool validateUsesProcVar(PKBReader& reader,
                                  const vector<string>& procs,
                                  ProcToStrSetMap expectedUsesMap);

  static bool validateCalls(PKBReader& reader, const vector<string>& procs,
                            ProcToStrSetMap expectedCallsMap);

  static bool validateCallsT(PKBReader& reader, const vector<string>& procs,
                             ProcToStrSetMap expectedCallsTMap);
};
