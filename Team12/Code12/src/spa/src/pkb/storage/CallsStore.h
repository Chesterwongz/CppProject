#pragma once

#include <string>

#include "RelationTStore.h"

class CallsStore : public RelationTStore<std::string, std::string> {
 public:
  void addRelation(const std::string& callerProc, const std::string& calleeProc,
                   int stmtNum) {
    RelationTStore::addRelation(callerProc, calleeProc);
    // TODO(PKB): add stmt -> calleeProc
  }
};
