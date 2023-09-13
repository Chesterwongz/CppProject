#include <string>

#include "../IArgument.h"
#include "Wildcard.h"

string Wildcard::getValue() {
	return wildcardValue;
}

string Wildcard::getArgumentType() {
	return argumentType;
}
