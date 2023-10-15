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
  static void printEntities(const string& abstraction,
                            const unordered_set<string>& set);
  static void printDifferences(const StrStrPairVec& actual,
                               const StrStrPairVec& expected);

 public:
  template <typename T>
  static bool compareVectorContents(vector<T> a, vector<T> b);

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
                              StrStrPairVec& expectedFollowsPairs,
                              StrStrPairVec& expectedFollowsTPairs);

  static bool validateParents(PKBReader& reader,
                              StrStrPairVec& expectedParentChildPairs,
                              StrStrPairVec& expectedParentChildTPairs);

  static bool validateModifies(PKBReader& reader,
                               StrStrPairVec& expectedModifiesPairs);

  static bool validateUses(PKBReader& reader, StrStrPairVec& expectedUsesPairs);

  static bool isAssignResultMatch(StrStrPairVec actual, StrStrPairVec expected);

  static bool validateModifiesProcVar(PKBReader& reader,
                                      const vector<string>& procs,
                                      ProcToStrSetMap& expectedModifiesMap);

  static bool validateUsesProcVar(PKBReader& reader,
                                  const vector<string>& procs,
                                  ProcToStrSetMap& expectedUsesMap);

  static bool validateCalls(PKBReader& reader, const vector<string>& procs,
                            ProcToStrSetMap& expectedCallsMap);

  static bool validateCallsT(PKBReader& reader, const vector<string>& procs,
                             ProcToStrSetMap& expectedCallsTMap);
};
