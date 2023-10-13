#include "CallsSynonymRes.h"

CallSynonymRes::CallSynonymRes(string& stmtNumber, string& procName)
    : StmtSynonymRes(stmtNumber) {
  this->attributeMap[AttrRef::PROC_NAME_ENUM] = procName;
}

SynonymRes CallSynonymRes::clone() const {
  string stmtNumberCopy = this->attributeMap.at(AttrRef::STMT_NUM_ENUM);
  string procNameCopy = this->attributeMap.at(AttrRef::PROC_NAME_ENUM);
  return CallSynonymRes(stmtNumberCopy, procNameCopy);
}
