#include "HelperFunctions.h"

#include <utility>

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
    PKBReader& reader, const set<string>& expectedVars,
    const set<string>& expectedConstants, const set<string>& expectedProcedures,
    const set<string>& expectedReadStmts, const set<string>& expectedPrintStmts,
    const set<string>& expectedAssignStmts,
    const set<string>& expectedCallStmts, const set<string>& expectedWhileStmts,
    const set<string>& expectedIfStmts) {
  bool areVariablesEqual = reader.getAllVariables() == expectedVars;
  bool areConstantsEqual = reader.getAllConstants() == expectedConstants;
  bool areProceduresEqual = reader.getAllProcedures() == expectedProcedures;
  bool areReadStmtsEqual =
      reader.getStatement(StmtType::READ) == expectedReadStmts;
  bool arePrintStmtsEqual =
      reader.getStatement(StmtType::PRINT) == expectedPrintStmts;
  bool areAssignStmtsEqual =
      reader.getStatement(StmtType::ASSIGN) == expectedAssignStmts;
  bool areCallStmtsEqual =
      reader.getStatement(StmtType::CALL) == expectedCallStmts;
  bool areWhileStmtsEqual =
      reader.getStatement(StmtType::WHILE) == expectedWhileStmts;
  bool areIfStmtsEqual = reader.getStatement(StmtType::IF) == expectedIfStmts;

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
  StrStrPairVec actual = reader.getAllModifiedVariables(StmtType::STMT);
  return compareVectorContents(actual, expectedModifiesPairs);
}

bool HelperFunctions::validateUses(PKBReader& reader,
                                   StrStrPairVec& expectedUsesPairs) {
  StrStrPairVec actual = reader.getAllUsedVariables(StmtType::STMT);
  return compareVectorContents(actual, expectedUsesPairs);
}

bool HelperFunctions::isAssignResultMatch(StrStrPairVec actual,
                                          StrStrPairVec expected) {
  return compareVectorContents(std::move(actual), std::move(expected));
}

bool HelperFunctions::validateModifiesProcVar(
    PKBReader& reader, const vector<string>& procs,
    ProcToStrSetMap& expectedModifiesMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedModifies = expectedModifiesMap[proc];
    vector<string> expectedModifiesVector(expectedModifies.begin(),
                                          expectedModifies.end());
    vector<string> actualModifies = reader.getModifiedVariablesForProc(proc);
    if (!compareVectorContents(actualModifies, expectedModifiesVector)) {
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
    vector<string> expectedUsesVector(expectedUses.begin(), expectedUses.end());
    vector<string> actualUses = reader.getUsedVariablesForProc(proc);
    if (!compareVectorContents(actualUses, expectedUsesVector)) {
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
    unordered_set<string> actualCalls = reader.getCalleeProcs(proc);
    if (actualCalls != expectedCalls) {
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
    unordered_set<string> actualCallsT = reader.getCalleeProcsStar(proc);
    if (actualCallsT != expectedCallsT) {
      return false;
    }
  }
  return true;
}
