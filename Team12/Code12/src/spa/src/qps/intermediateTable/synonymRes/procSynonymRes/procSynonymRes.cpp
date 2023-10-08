#include "procSynonymRes.h"

ProcSynonymRes::ProcSynonymRes(const string& defaultSynonymValue)
    : SynonymRes(defaultSynonymValue) {
  this->attributeMap[AttrRef::PROC_NAME_ENUM] = defaultSynonymValue;
}
