#include "HelperFunctions.h"

void HelperFunctions::printEntities(const string& abstraction,
                                    const unordered_set<string>& set) {
  std::cout << abstraction << ": ";
  for (const string& entity : set) {
    std::cout << entity << ", ";
  }
  std::cout << std::endl << "-------------" << std::endl;
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
                                      StrStrPairSet& expectedFollowsPairs,
                                      StrStrPairSet& expectedFollowsTPairs) {
  vector<pair<string, string>> actualFollowsPairs =
      reader.getFollowsPairs(StmtType::STMT, StmtType::STMT);
  StrStrPairSet actualFollows = {actualFollowsPairs.begin(),
                                 actualFollowsPairs.end()};
  vector<pair<string, string>> actualFollowsTPairs =
      reader.getFollowsStarPairs(StmtType::STMT, StmtType::STMT);
  StrStrPairSet actualFollowsT = {actualFollowsTPairs.begin(),
                                  actualFollowsTPairs.end()};
  bool isFollowsEqual = actualFollows == expectedFollowsPairs;
  bool isFollowsTEqual = actualFollowsT == expectedFollowsTPairs;
  return isFollowsEqual && isFollowsTEqual;
}

bool HelperFunctions::validateParents(
    PKBReader& reader, StrStrPairSet& expectedParentChildPairs,
    StrStrPairSet& expectedParentChildTPairs) {
  vector<pair<string, string>> actualParentChildPairs =
      reader.getParentChildPairs(StmtType::STMT, StmtType::STMT);
  StrStrPairSet actualParentChildSet = {actualParentChildPairs.begin(),
                                        actualParentChildPairs.end()};
  vector<pair<string, string>> actualParentChildTPairs =
      reader.getParentChildStarPairs(StmtType::STMT, StmtType::STMT);
  StrStrPairSet actualParentChildTSet = {actualParentChildTPairs.begin(),
                                         actualParentChildTPairs.end()};
  bool isParentEqual = actualParentChildSet == expectedParentChildPairs;
  bool isParentTEqual = actualParentChildTSet == expectedParentChildTPairs;
  return isParentEqual && isParentTEqual;
}

bool HelperFunctions::validateModifies(PKBReader& reader,
                                       StrStrPairSet& expectedModifiesPairs) {
  vector<pair<string, string>> actual =
      reader.getAllModifiedVariables(StmtType::STMT);
  StrStrPairSet actualModifiesPairs = {actual.begin(), actual.end()};
  return actualModifiesPairs == expectedModifiesPairs;
}

bool HelperFunctions::validateUses(PKBReader& reader,
                                   StrStrPairSet& expectedUsesPairs) {
  vector<pair<string, string>> actual =
      reader.getAllUsedVariables(StmtType::STMT);
  StrStrPairSet actualUsesPairs = {actual.begin(), actual.end()};
  return actualUsesPairs == expectedUsesPairs;
}

bool HelperFunctions::isAssignResultMatch(vector<string> actual,
                                          unordered_set<string> expected) {
  unordered_set<string> actualSet = {actual.begin(), actual.end()};
  return actualSet == expected;
}

bool HelperFunctions::validateModifiesProcVar(
    PKBReader& reader, const vector<string>& procs,
    ProcToStrSetMap expectedModifiesMap) {
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
                                          ProcToStrSetMap expectedUsesMap) {
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
                                    ProcToStrSetMap expectedCallsMap) {
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
                                     ProcToStrSetMap expectedCallsTMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedCallsT = expectedCallsTMap[proc];
    unordered_set<string> actualCallsT = reader.getCalleeProcsStar(proc);
    if (actualCallsT != expectedCallsT) {
      return false;
    }
  }
  return true;
}
