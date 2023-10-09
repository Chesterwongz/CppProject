#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

class ICallsReader {
 public:
  virtual ~ICallsReader() = default;
  virtual std::unordered_set<std::string> getCallerProcs(
      const std::string& procName) = 0;
  virtual std::unordered_set<std::string> getCallerProcsStar(
      const std::string& procName) = 0;
  virtual std::unordered_set<std::string> getCalleeProcs(
      const std::string& procName) = 0;
  virtual std::unordered_set<std::string> getCalleeProcsStar(
      const std::string& procName) = 0;
  virtual std::unordered_set<std::string> getAllCallerProcs() = 0;
  virtual std::unordered_set<std::string> getAllCalleeProcs() = 0;
  virtual bool isCalling(const std::string& caller,
                         const std::string& callee) = 0;
  virtual bool isCallingStar(const std::string& caller,
                             const std::string& callee) = 0;
};
