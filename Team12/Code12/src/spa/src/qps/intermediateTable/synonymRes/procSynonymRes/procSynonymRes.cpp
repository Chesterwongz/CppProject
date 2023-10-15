#include "procSynonymRes.h"

ProcSynonymRes::ProcSynonymRes(const string& defaultSynonymValue)
    : SynonymRes(defaultSynonymValue) {
  this->attributeMap[AttrRef::PROC_NAME_ENUM] = defaultSynonymValue;
}

unique_ptr<SynonymRes> ProcSynonymRes::clone() const {
  string synonymValueCopy = this->defaultSynonymValue;
  return std::move(std::make_unique<ProcSynonymRes>(synonymValueCopy));
}
