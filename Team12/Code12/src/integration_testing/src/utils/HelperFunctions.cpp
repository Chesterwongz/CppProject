#include "HelperFunctions.h"

void HelperFunctions::printEntities(const string& abstraction,
                                    const unordered_set<string>& set) {
  std::cout << abstraction << ": ";
  for (const string& entity : set) {
    std::cout << entity << ", ";
  }
  std::cout << std::endl << "-------------" << std::endl;
}

void HelperFunctions::printDifferences(const StrStrPairVec& actual,
                                       const StrStrPairVec& expected) {
  StrStrPairSet actualCopy = {actual.begin(), actual.end()};
  StrStrPairSet expectedCopy = {expected.begin(), expected.end()};
  for (const auto& actualPair : actual) {
    if (expectedCopy.find(actualPair) != expectedCopy.end()) {
      expectedCopy.erase(actualPair);
      actualCopy.erase(actualPair);
    }
  }
  std::cout << "Actual - Expected: " << std::endl;
  for (const auto& actualPair : actualCopy) {
    std::cout << actualPair.first << ", " << actualPair.second << std::endl;
  }
  std::cout << "Expected - Actual: " << std::endl;
  for (const auto& expectedPair : expectedCopy) {
    std::cout << expectedPair.first << ", " << expectedPair.second << std::endl;
  }
}

template <typename T>
bool HelperFunctions::compareVectorContents(vector<T> a, vector<T> b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (T& item : a) {
    bool isSameCountInBoth = std::count(a.begin(), a.end(), item) ==
                             std::count(b.begin(), b.end(), item);
    if (!isSameCountInBoth) {
      return false;
    }
  }
  return true;
}

bool HelperFunctions::validateEntities(
    PKBReader& reader, const vector<string>& expectedVars,
    const vector<string>& expectedConstants,
    const vector<string>& expectedProcedures,
    const vector<string>& expectedReadStmts,
    const vector<string>& expectedPrintStmts,
    const vector<string>& expectedAssignStmts,
    const vector<string>& expectedCallStmts,
    const vector<string>& expectedWhileStmts,
    const vector<string>& expectedIfStmts) {
  vector<string> actualVars = reader.getAllVariables();
  vector<string> actualConstants = reader.getAllConstants();
  vector<string> actualProcedures = reader.getAllProcedures();
  vector<string> actualReadStmts = reader.getAllStmtsOf(StmtType::READ);
  vector<string> actualPrintStmts = reader.getAllStmtsOf(StmtType::PRINT);
  vector<string> actualAssignStmts = reader.getAllStmtsOf(StmtType::ASSIGN);
  vector<string> actualCallStmts = reader.getAllStmtsOf(StmtType::CALL);
  vector<string> actualWhileStmts = reader.getAllStmtsOf(StmtType::WHILE);
  vector<string> actualIfStmts = reader.getAllStmtsOf(StmtType::IF);

  bool areVariablesEqual = compareVectorContents(actualVars, expectedVars);
  bool areConstantsEqual =
      compareVectorContents(actualConstants, expectedConstants);
  bool areProceduresEqual =
      compareVectorContents(actualProcedures, expectedProcedures);
  bool areReadStmtsEqual =
      compareVectorContents(actualReadStmts, expectedReadStmts);
  bool arePrintStmtsEqual =
      compareVectorContents(actualPrintStmts, expectedPrintStmts);
  bool areAssignStmtsEqual =
      compareVectorContents(actualAssignStmts, expectedAssignStmts);
  bool areCallStmtsEqual =
      compareVectorContents(actualCallStmts, expectedCallStmts);
  bool areWhileStmtsEqual =
      compareVectorContents(actualWhileStmts, expectedWhileStmts);
  bool areIfStmtsEqual = compareVectorContents(actualIfStmts, expectedIfStmts);

  return areVariablesEqual && areConstantsEqual && areProceduresEqual &&
         areReadStmtsEqual && arePrintStmtsEqual && areAssignStmtsEqual &&
         areCallStmtsEqual && areWhileStmtsEqual && areIfStmtsEqual;
}

bool HelperFunctions::validateFollows(PKBReader& reader,
                                      StrStrPairVec& expectedFollowsPairs,
                                      StrStrPairVec& expectedFollowsTPairs) {
  StrStrPairVec actualFollowsPairs =
      reader.getFollowsPairs(StmtType::STMT, StmtType::STMT);
  StrStrPairVec actualFollowsTPairs =
      reader.getFollowsStarPairs(StmtType::STMT, StmtType::STMT);
  bool isFollowsEqual =
      compareVectorContents(actualFollowsPairs, expectedFollowsPairs);
  bool isFollowsTEqual =
      compareVectorContents(actualFollowsTPairs, expectedFollowsTPairs);
  return isFollowsEqual && isFollowsTEqual;
}

bool HelperFunctions::validateParents(
    PKBReader& reader, StrStrPairVec& expectedParentChildPairs,
    StrStrPairVec& expectedParentChildTPairs) {
  StrStrPairVec actualParentChildPairs =
      reader.getParentChildPairs(StmtType::STMT, StmtType::STMT);
  StrStrPairVec actualParentChildTPairs =
      reader.getParentChildStarPairs(StmtType::STMT, StmtType::STMT);
  bool isParentEqual =
      compareVectorContents(actualParentChildPairs, expectedParentChildPairs);
  bool isParentTEqual =
      compareVectorContents(actualParentChildTPairs, expectedParentChildTPairs);
  return isParentEqual && isParentTEqual;
}

bool HelperFunctions::validateModifies(PKBReader& reader,
                                       StrStrPairVec& expectedModifiesPairs) {
  StrStrPairVec actual = reader.getModifiesPairs(StmtType::STMT);
  return compareVectorContents(actual, expectedModifiesPairs);
}

bool HelperFunctions::validateUses(PKBReader& reader,
                                   StrStrPairVec& expectedUsesPairs) {
  StrStrPairVec actual = reader.getUsesPairs(StmtType::STMT);
  return compareVectorContents(actual, expectedUsesPairs);
}

bool HelperFunctions::isAssignResultMatch(StrStrPairVec actual,
                                          StrStrPairVec expected) {
  return compareVectorContents(actual, expected);
}

bool HelperFunctions::validateModifiesProcVar(
    PKBReader& reader, const vector<string>& procs,
    ProcToStrSetMap& expectedModifiesMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedModifies = expectedModifiesMap[proc];
    unordered_set<string> actualModifies =
        reader.getModifiedVariablesForProc(proc);
    if (actualModifies != expectedModifies) {
      return false;
    }
  }
  return true;
}

bool HelperFunctions::validateUsesProcVar(PKBReader& reader,
                                          const vector<string>& procs,
                                          ProcToStrSetMap& expectedUsesMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedUses = expectedUsesMap[proc];
    unordered_set<string> actualUses = reader.getUsedVariablesForProc(proc);
    if (actualUses != expectedUses) {
      return false;
    }
  }
  return true;
}

bool HelperFunctions::validateCalls(PKBReader& reader,
                                    const vector<string>& procs,
                                    ProcToStrSetMap& expectedCallsMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedCalls = expectedCallsMap[proc];
    vector<string> expectedCallsVec = {expectedCalls.begin(),
                                       expectedCalls.end()};
    vector<string> actualCalls = reader.getCalleeProcs(proc);
    if (!compareVectorContents(actualCalls, expectedCallsVec)) {
      return false;
    }
  }
  return true;
}

bool HelperFunctions::validateCallsT(PKBReader& reader,
                                     const vector<string>& procs,
                                     ProcToStrSetMap& expectedCallsTMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedCallsT = expectedCallsTMap[proc];
    vector<string> expectedCallsTVec = {expectedCallsT.begin(),
                                        expectedCallsT.end()};
    vector<string> actualCallsT = reader.getCalleeProcsStar(proc);
    if (!compareVectorContents(actualCallsT, expectedCallsTVec)) {
      return false;
    }
  }
  return true;
}
