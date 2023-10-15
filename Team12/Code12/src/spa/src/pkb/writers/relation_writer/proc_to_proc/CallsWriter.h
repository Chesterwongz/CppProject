#pragma once

#include <string>

#include "pkb/storage/CallsStore.h"
#include "pkb/interfaces/writers/ICallsWriter.h"

class CallsWriter : public ICallsWriter {
 private:
  CallsStore& callsStore;

 protected:
  explicit CallsWriter(CallsStore& callsStore) : callsStore(callsStore) {}

 public:
  void addCalls(const std::string& callerProc, const std::string& calleeProc,
                int stmtNum) override;
};
