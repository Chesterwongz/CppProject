#include "SynonymArg.h"

#include <string>

#include "qps/exceptions/QPSInvalidQueryException.h"

const string& SynonymArg::getValue() { return synonymValue; }

const Entity& SynonymArg::getEntityType() { return entityType; }

void SynonymArg::setAttrRef(AttrRef ref) { this->attrRef = std::move(ref); }

const AttrRef& SynonymArg::getAttrRef() { return this->attrRef; }

QPSStringUtils::ArgumentType SynonymArg::getArgumentType() {
  return argumentType;
}

bool SynonymArg::isSynonym() { return true; }

bool SynonymArg::isStmtSynonym() {
  return STATEMENT_ENTITIES.find(entityType) != STATEMENT_ENTITIES.end();
}

bool SynonymArg::isVarSynonym() { return entityType == VARIABLE_ENTITY; }

bool SynonymArg::isProcSynonym() { return entityType == PROCEDURE_ENTITY; }

bool SynonymArg::operator==(const AbstractArgument& other) const {
  const auto* otherSynonym = dynamic_cast<const SynonymArg*>(&other);
  if (!otherSynonym) return false;

  return this->synonymValue == otherSynonym->synonymValue &&
         this->entityType == otherSynonym->entityType &&
         this->attrRef == otherSynonym->attrRef;
}
