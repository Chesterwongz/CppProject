#pragma once

#include <string>
#include <vector>

#include "pkb/interfaces/readers/ICallsReader.h"
#include "pkb/storage/CallsStore.h"
#include "pkb/utils/PredicateUtils.h"

class CallsReader : public ICallsReader {
 private:
  CallsStore& callsStore;

 public:
  explicit CallsReader(CallsStore& callsStore) : callsStore(callsStore) {}

  // Calls(p, "proc1"), returns all p
  std::vector<std::string> getCallerProcs(const std::string& proc1) override;

  // Calls*(p, "proc1"), returns all p
  std::vector<std::string> getCallerProcsStar(
      const std::string& proc1) override;

  // Calls("proc2", p), returns all p
  std::vector<std::string> getCalleeProcs(const std::string& proc2) override;

  // Calls*("proc2", p), returns all p
  std::vector<std::string> getCalleeProcsStar(
      const std::string& proc2) override;

  // Calls(p1, p2)
  std::vector<std::pair<std::string, std::string>> getCallPairs() override;

  // Calls*(p1, p2)
  std::vector<std::pair<std::string, std::string>> getCallsStarPairs() override;

  bool hasCalls(const std::string& proc1, const std::string& proc2) override;

  bool hasCallsT(const std::string& proc1, const std::string& proc2) override;
};
