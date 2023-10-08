#include "ConstantSynonymRes.h"

ConstantSynonymRes::ConstantSynonymRes(const string& defaultSynonymValue)
    : SynonymRes(defaultSynonymValue) {
  this->attributeMap[AttrRef::VALUE_ENUM] = defaultSynonymValue;
}
