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

void HelperFunctions::printDifferences(const vector<string>& actual,
                                       const vector<string>& expected) {
  unordered_set<string> actualCopy = {actual.begin(), actual.end()};
  unordered_set<string> expectedCopy = {expected.begin(), expected.end()};
  for (const auto& actualStr : actual) {
    if (expectedCopy.find(actualStr) != expectedCopy.end()) {
      expectedCopy.erase(actualStr);
      actualCopy.erase(actualStr);
    }
  }
  std::cout << "Actual - Expected: " << std::endl;
  for (const auto& actualStr : actualCopy) {
    std::cout << actualStr << ", ";
  }
  std::cout << std::endl << "-------------" << std::endl;
  std::cout << "Expected - Actual: " << std::endl;
  for (const auto& expectedStr : expectedCopy) {
    std::cout << expectedStr << ", ";
  }
  std::cout << std::endl << "-------------" << std::endl;
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
  StrStrPairVec actual = reader.getModifiesStmtPairs(StmtType::STMT);
  return compareVectorContents(actual, expectedModifiesPairs);
}

bool HelperFunctions::validateUses(PKBReader& reader,
                                   StrStrPairVec& expectedUsesPairs) {
  StrStrPairVec actual = reader.getUsesStmtPairs(StmtType::STMT);
  return compareVectorContents(actual, expectedUsesPairs);
}

bool HelperFunctions::isAssignResultMatch(StrStrPairVec actual,
                                          StrStrPairVec expected) {
  return compareVectorContents(std::move(actual), std::move(expected));
}

template <typename S, typename T>
bool HelperFunctions::validateWithMap(
    PKBReader& reader, const vector<S>& elements,
    const unordered_map<S, vector<string>>& expectedMap,
    std::function<vector<string>(PKBReader&, T)> getActual) {
  for (const S& element : elements) {
    if (!expectedMap.count(element)) {
      return getActual(reader, element).empty();
    }
    vector<string> expected = expectedMap.at(element);
    vector<string> actual = getActual(reader, element);
    if (!compareVectorContents(actual, expected)) {
      printDifferences(actual, expected);
      return false;
    }
  }
  return true;
}

bool HelperFunctions::validateModifiesProcVar(
    PKBReader& reader, const vector<string>& procs,
    const StrToStrVecMap& expectedModifiesMap) {
  return validateWithMap<string, const string&>(
      reader, procs, expectedModifiesMap,
      [](PKBReader& r, const string& p) { return r.getVarsModifiedByProc(p); });
}

bool HelperFunctions::validateUsesProcVar(
    PKBReader& reader, const vector<string>& procs,
    const StrToStrVecMap& expectedUsesMap) {
  return validateWithMap<string, const string&>(
      reader, procs, expectedUsesMap,
      [](PKBReader& r, const string& p) { return r.getVarsUsedByProc(p); });
}

bool HelperFunctions::validateCalls(PKBReader& reader,
                                    const vector<string>& procs,
                                    const StrToStrVecMap& expectedCallsMap) {
  return validateWithMap<string, const string&>(
      reader, procs, expectedCallsMap,
      [](PKBReader& r, const string& p) { return r.getCalleeProcs(p); });
}

bool HelperFunctions::validateCallsT(PKBReader& reader,
                                     const vector<string>& procs,
                                     const StrToStrVecMap& expectedCallsTMap) {
  return validateWithMap<string, const string&>(
      reader, procs, expectedCallsTMap,
      [](PKBReader& r, const string& p) { return r.getCalleeProcsStar(p); });
}

bool HelperFunctions::validateNext(PKBReader& reader, const vector<int>& stmts,
                                   const IntToStrVecMap& expectedNextMap) {
  return validateWithMap<int, int>(
      reader, stmts, expectedNextMap,
      [](PKBReader& r, int s) { return r.getNextStmts(s, StmtType::STMT); });
}

bool HelperFunctions::validateNextT(PKBReader& reader, const vector<int>& stmts,
                                    const IntToStrVecMap& expectedNextTMap) {
  return validateWithMap<int, int>(
      reader, stmts, expectedNextTMap,
      [](PKBReader& r, int s) { return r.getNextTStmts(s, StmtType::STMT); });
}
