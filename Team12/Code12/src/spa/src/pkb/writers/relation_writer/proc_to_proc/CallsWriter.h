#pragma once

#include <string>

#include "pkb/interfaces/writers/ICallsWriter.h"
#include "pkb/storage/CallsSStore.h"
#include "pkb/storage/CallsStore.h"

class CallsWriter : public ICallsWriter {
 private:
  CallsStore& callsStore;
  CallsSStore& callsStmtStore;

 protected:
  explicit CallsWriter(CallsStore& callsStore, CallsSStore& callsStmtStore)
      : callsStore(callsStore), callsStmtStore(callsStmtStore) {}

 public:
  void addCalls(const std::string& callerProc, const std::string& calleeProc,
                int stmtNum) override;
};
