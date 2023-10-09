#pragma once

#include <string>
#include <utility>
#include <unordered_set>
#include <vector>

class ICallsReader {
 public:
  virtual unordered_set<string> getCallerProcs(const std::string& procName) = 0;
  virtual unordered_set<string> getCallerProcsStar(
      const std::string& procName) = 0;
  virtual unordered_set<string> getCalleeProcs(const std::string& procName) = 0;
  virtual unordered_set<string> getCalleeProcsStar(
      const std::string& procName) = 0;
  virtual unordered_set<string> getAllCallerProcs() = 0;
  virtual unordered_set<string> getAllCalleeProcs() = 0;
  virtual bool isCalling(const std::string& caller,
                         const std::string& callee) = 0;
  virtual bool isCallingStar(const std::string& caller,
                             const std::string& callee) = 0;
};
