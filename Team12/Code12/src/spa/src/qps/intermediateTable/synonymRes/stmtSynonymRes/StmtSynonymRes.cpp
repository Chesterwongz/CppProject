#include "StmtSynonymRes.h"

StmtSynonymRes::StmtSynonymRes(const string& defaultSynonymValue)
    : SynonymRes(defaultSynonymValue) {
  this->attributeMap[AttrRef::STMT_NUM_ENUM] = defaultSynonymValue;
}

unique_ptr<SynonymRes> StmtSynonymRes::clone() const {
  string synonymValueCopy = this->defaultSynonymValue;
  return std::move(std::make_unique<StmtSynonymRes>(synonymValueCopy));
}
