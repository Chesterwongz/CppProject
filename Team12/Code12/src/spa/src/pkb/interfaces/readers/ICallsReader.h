#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

class ICallsReader {
 public:
  virtual ~ICallsReader() = default;
  virtual std::vector<std::string> getCallerProcs(const std::string& procName) = 0;
  virtual std::vector<std::string> getCallerProcsStar(const std::string& procName) = 0;
  virtual std::vector<std::string> getCalleeProcs(const std::string& procName) = 0;
  virtual std::vector<std::string> getCalleeProcsStar(const std::string& procName) = 0;
  virtual std::vector<std::pair<std::string, std::string>> getCallPairs() = 0;
  virtual std::vector<std::pair<std::string, std::string>> getCallsStarPairs() = 0;
  virtual bool hasCalls(const std::string& caller,
                        const std::string& callee) = 0;
  virtual bool hasCallsT(const std::string& caller,
                         const std::string& callee) = 0;
};
