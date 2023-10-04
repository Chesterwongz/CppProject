#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class CallsStorage {
public:
    void setCallsRelationship(const std::string& caller, const std::string& callee, int statementNumber);
    void setCallsStarRelationship(const std::string& caller, const std::string& callee, int statementNumber);

    // return pairs (stmtNum, calleeName) that are directly called by procName
    std::vector<std::pair<std::string, std::string>> getCalls(const std::string& procedure);

    // return pairs (stmtNum, caleeName) that are indirectly called by procName
    std::vector<std::pair<std::string, std::string>> getCallsStar(const std::string& procedure);

    // return pairs (stmtNum, callerName) that directly call procName
    std::vector<std::pair<std::string, std::string>> getCalledBy(const std::string& procedure);

    // return pairs (stmtNum, callerName) that indirectly call procName
    std::vector<std::pair<std::string, std::string>> getCalledByStar(const std::string& procedure);

    bool isCalls(const std::string& caller, const std::string& callee);
    bool isCallsStar(const std::string& caller, const std::string& callee);

    bool isCallingStmt(int stmtNum, const std::string& callee);
    bool isCallingStarStmt(int stmtNum, const std::string& callee);

    // return all pairs (stmtNum, callerName) that call another procedure
    std::vector<std::pair<std::string, std::string>> getCallingProcedures();

    // return all pairs (stmtNum, calleeName) that are called by another procedure
    std::vector<std::pair<std::string, std::string>> getCalledProcedures();

    // return procedure that is called on stmtNum 
    virtual std::string getProcCalledOn(int stmtNum);

    // return list of procedures names that are indirectly called on stmtNum
    virtual std::vector<std::string> getProcStarCalledOn(int stmtNum);


private:
    // callerProc -> [stmtNum, calleeProc]
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> callsMap;
    // callerProc -> [stmtNum, calleeProc]
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> callsStarMap;
    // calleeProc -> [stmtNum, callerProc]
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> calledByMap;
    // calleeProc -> [stmtNum, callerProc]
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> calledByStarMap;
};
