#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

class ICallsReader {
 public:
  virtual ~ICallsReader() = default;
  virtual vector<string> getCallerProcs(const std::string& procName) = 0;
  virtual vector<string> getCallerProcsStar(const std::string& procName) = 0;
  virtual vector<string> getCalleeProcs(const std::string& procName) = 0;
  virtual vector<string> getCalleeProcsStar(const std::string& procName) = 0;
  virtual vector<std::pair<string, string>> getCallPairs() = 0;
  virtual vector<std::pair<string, string>> getCallsStarPairs() = 0;
  virtual bool hasCalls(const std::string& caller,
                        const std::string& callee) = 0;
  virtual bool hasCallsT(const std::string& caller,
                         const std::string& callee) = 0;
};
