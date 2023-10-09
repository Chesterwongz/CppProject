#pragma once

#include <string>
#include <unordered_set>

#include "pkb/interfaces/readers/ICallsReader.h"
#include "pkb/storage/relation_storage/proc_to_proc/CallsStorage.h"

class CallsReader : public ICallsReader {
 private:
  CallsStorage& callsStorage;

 public:
  explicit CallsReader(CallsStorage& callsStorage)
      : callsStorage(callsStorage) {}
  unordered_set<string> getCallerProcs(const std::string& procName) override;

  unordered_set<string> getCallerProcsStar(
      const std::string& procName) override;

  unordered_set<string> getCalleeProcs(const std::string& procName) override;

  unordered_set<string> getCalleeProcsStar(
      const std::string& procName) override;

  unordered_set<string> getAllCallerProcs() override;

  unordered_set<string> getAllCalleeProcs() override;

  bool isCalling(const std::string& caller, const std::string& callee) override;

  bool isCallingStar(const std::string& caller,
                     const std::string& callee) override;
};
