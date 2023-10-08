#pragma once

#include <string>
#include <utility>
#include <vector>

class ICallsReader {
 public:
  virtual std::vector<std::pair<std::string, std::string>> getCallerProcs(
      const std::string& procName) = 0;
  virtual std::vector<std::pair<std::string, std::string>> getCallerProcsStar(
      const std::string& procName) = 0;
  virtual std::vector<std::pair<std::string, std::string>> getCalleeProcs(
      const std::string& procName) = 0;
  virtual std::vector<std::pair<std::string, std::string>> getCalleeProcsStar(
      const std::string& procName) = 0;
  virtual std::string getProcCalledOn(int stmtNum) = 0;
  virtual std::vector<std::string> getProcStarCalledOn(int stmtNum) = 0;
  virtual std::vector<std::pair<std::string, std::string>>
  getCallingProcedures() = 0;
  virtual std::vector<std::pair<std::string, std::string>>
  getCalledProcedures() = 0;
  virtual bool isCalling(const std::string& caller,
                         const std::string& callee) = 0;
  virtual bool isCallingStar(const std::string& caller,
                             const std::string& callee) = 0;
  virtual bool isCallingStmt(int stmtNum, const std::string& callee) = 0;
  virtual bool isCallingStarStmt(int stmtNum, const std::string& callee) = 0;
};
