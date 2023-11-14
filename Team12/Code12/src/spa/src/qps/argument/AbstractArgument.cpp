#include "AbstractArgument.h"

bool AbstractArgument::isIdent() { return false; }
bool AbstractArgument::isInteger() { return false; }
bool AbstractArgument::isSynonym() const { return false; }
bool AbstractArgument::isStmtSynonym() { return false; }
bool AbstractArgument::isVarSynonym() { return false; }
bool AbstractArgument::isProcSynonym() { return false; }
bool AbstractArgument::isWildcard() { return false; }
bool AbstractArgument::isPatternExp() { return false; }

string AbstractArgument::getArgKey() {
  return this->getValue() + AbstractArgument::ARG_KEY_DELIMITER +
         QPSStringUtils::ArgTypeToKeyMap.at(this->getArgumentType());
}

string AbstractArgument::getArgSignature() {
  return this->getArgKey();
}


