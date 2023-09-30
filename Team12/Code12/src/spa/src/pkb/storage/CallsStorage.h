#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

class CallsStorage {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> callsMap;
    std::unordered_map<std::string, std::unordered_set<std::string>> callsStarMap;
    std::unordered_map<std::string, std::unordered_set<std::string>> calledByMap;
    std::unordered_map<std::string, std::unordered_set<std::string>> calledByStarMap;

public:
    CallsStorage() = default;
    ~CallsStorage() = default;
    void setCalls(const std::string& callerProc, const std::string& calleeProc);
    void setCallsStar(const std::string& callerProc, const std::string& calleeProc);
    const std::unordered_map<std::string, std::unordered_set<std::string>>& getCallsMap();
    std::unordered_set<std::string> getDirectProcsCalledBy(const std::string& callerProc);
    std::unordered_set<std::string> getAllProcsCalledBy(const std::string& callerProc);
};
