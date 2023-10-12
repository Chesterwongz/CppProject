#include "AbstractArgument.h"

bool AbstractArgument::isIdent() { return false; }
bool AbstractArgument::isInteger() { return false; }
bool AbstractArgument::isSynonym() { return false; }
bool AbstractArgument::isWildcard() { return false; }
bool AbstractArgument::isPatternExp() { return false; }
