#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

using std::unordered_set, std::unordered_map, std::string;

class CallsStorage {
 private:
  unordered_map<string, unordered_set<string>> callsMap;
  unordered_map<string, unordered_set<string>> callsStarMap;
  unordered_map<string, unordered_set<string>> calledByMap;
  unordered_map<string, unordered_set<string>> calledByStarMap;

 public:
  CallsStorage() = default;
  ~CallsStorage() = default;
  void setCalls(const string& callerProc, const string& calleeProc);
  void setCallsStar(const string& callerProc, const string& calleeProc);
  const unordered_map<string, unordered_set<string>>& getCallsMap();
  unordered_set<string> getDirectProcsCalledBy(const string& callerProc);
  unordered_set<string> getAllProcsCalledBy(const string& callerProc);
};
