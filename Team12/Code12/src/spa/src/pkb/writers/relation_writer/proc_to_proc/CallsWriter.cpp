#include "CallsWriter.h"

void CallsWriter::addCalls(const std::string& callerProc,
                           const std::string& calleeProc, int stmtNum) {
  callsStore.addRelation(callerProc, calleeProc, stmtNum);
}
