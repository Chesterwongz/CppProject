#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::unordered_set, std::unordered_map, std::string, std::vector,
    std::pair, std::make_pair;

class CallsStorage {
 public:
  void setCallsRelationship(const string& caller, const string& callee,
                            int statementNumber);
  void setCallsStarRelationship(const string& caller, const string& callee,
                                int statementNumber);

  // return pairs (stmtNum, calleeName) that are directly called by procName
  vector<pair<string, string>> getCalleeProcs(const string& procedure);

  // return pairs (stmtNum, caleeName) that are indirectly called by procName
  vector<pair<string, string>> getCalleeProcsStar(const string& procedure);

  // return pairs (stmtNum, callerName) that directly call procName
  vector<pair<string, string>> getCallerProcs(const string& procedure);

  // return pairs (stmtNum, callerName) that indirectly call procName
  vector<pair<string, string>> getCallerProcsStar(const string& procedure);

  bool isCalls(const string& caller, const string& callee);
  bool isCallsStar(const string& caller, const string& callee);

  bool isCallingStmt(int stmtNum, const string& callee);
  bool isCallingStarStmt(int stmtNum, const string& callee);

  // return all pairs (stmtNum, callerName) that call another procedure
  vector<pair<string, string>> getCallingProcedures();

  // return all pairs (stmtNum, calleeName) that are called by another procedure
  vector<pair<string, string>> getCalledProcedures();

  // return procedure that is called on stmtNum
  virtual string getProcCalledOn(int stmtNum);

  // return list of procedures names that are indirectly called on stmtNum
  virtual vector<string> getProcStarCalledOn(int stmtNum);

  const unordered_map<string, vector<pair<int, string>>>& getCalleeProcsMap();

 private:
  // callerProc -> [stmtNum, calleeProc]
  unordered_map<string, vector<pair<int, string>>> callsMap;
  // callerProc -> [stmtNum, calleeProc]
  unordered_map<string, vector<pair<int, string>>> callsStarMap;
  // calleeProc -> [stmtNum, callerProc]
  unordered_map<string, vector<pair<int, string>>> calledByMap;
  // calleeProc -> [stmtNum, callerProc]
  unordered_map<string, vector<pair<int, string>>> calledByStarMap;
};
