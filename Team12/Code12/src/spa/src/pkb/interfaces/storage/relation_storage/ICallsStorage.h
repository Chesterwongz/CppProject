#pragma once

#include <string>
#include <unordered_set>
#include <utility>

#include "common/AliasTypes.h"

using std::string, std::unordered_set;

class ICallsStorage {
 public:
  virtual ~ICallsStorage() = default;
  virtual void setCallsRelationship(const string& caller, const string& callee,
                                    int stmtNum) = 0;
  virtual void setCallsStarRelationship(const string& caller,
                                        const string& callee) = 0;
  virtual unordered_set<string> getCalleeProcs(const string& caller) = 0;
  virtual unordered_set<string> getCalleeProcsStar(const string& caller) = 0;
  virtual unordered_set<string> getCallerProcs(const string& callee) = 0;
  virtual unordered_set<string> getCallerProcsStar(const string& callee) = 0;
  virtual bool isCalls(const string& caller, const string& callee) = 0;
  virtual bool isCallsStar(const string& caller, const string& callee) = 0;
  virtual unordered_set<string> getAllCallerProcs() = 0;
  virtual unordered_set<string> getAllCalleeProcs() = 0;
};
