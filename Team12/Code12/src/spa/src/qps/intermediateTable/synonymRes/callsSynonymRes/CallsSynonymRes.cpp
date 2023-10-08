#include "CallsSynonymRes.h"

CallSynonymRes::CallSynonymRes(string& stmtNumber, string& procName)
    : StmtSynonymRes(stmtNumber) {
  this->attributeMap[AttrRef::PROC_NAME_ENUM] = procName;
}
