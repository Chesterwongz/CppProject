#include "SynonymArg.h"

#include <string>

#include "qps/exceptions/QPSInvalidQueryException.h"

string SynonymArg::getValue() { return synonymValue; }

void SynonymArg::setAttrRef(AttrRef ref) { this->attrRef = std::move(ref); }

QPSStringUtils::ArgumentType SynonymArg::getArgumentType() {
  return argumentType;
}

bool SynonymArg::isSynonym() { return true; }

bool SynonymArg::operator==(const AbstractArgument& other) const {
  const auto* otherSynonym = dynamic_cast<const SynonymArg*>(&other);
  if (!otherSynonym) return false;

  return this->synonymValue == otherSynonym->synonymValue &&
         this->entityType == otherSynonym->entityType &&
         this->attrRef == otherSynonym->attrRef;
}
