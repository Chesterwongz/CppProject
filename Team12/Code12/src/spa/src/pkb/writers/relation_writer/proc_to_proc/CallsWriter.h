#pragma once

#include <string>

#include "pkb/interfaces/writers/ICallsWriter.h"
#include "pkb/storage/relation_storage/RelationStore.h"
#include "pkb/storage/relation_storage/RelationTStore.h"

class CallsWriter : public ICallsWriter {
 private:
  RelationTStore<std::string>& callsStore;
  RelationStore<int, std::string>& callsStmtStore;

 protected:
  explicit CallsWriter(RelationTStore<std::string>& callsStore,
                       RelationStore<int, std::string>& callsStmtStore)
      : callsStore(callsStore), callsStmtStore(callsStmtStore) {}

 public:
  void addCalls(const std::string& callerProc, const std::string& calleeProc,
                int stmtNum) override;
};
