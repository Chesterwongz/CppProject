#include "StmtSynonymRes.h"

StmtSynonymRes::StmtSynonymRes(const string& defaultSynonymValue)
    : SynonymRes(defaultSynonymValue) {
  this->attributeMap[AttrRef::STMT_NUM_ENUM] = defaultSynonymValue;
}

SynonymRes StmtSynonymRes::clone() const {
  string synonymValueCopy = this->defaultSynonymValue;
  return StmtSynonymRes(synonymValueCopy);
}
