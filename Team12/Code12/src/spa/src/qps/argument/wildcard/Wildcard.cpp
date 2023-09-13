#include <string>

#include <../IArgument.h>
#include "Wildcard.h"

string Wildcard::getValue() {
	return this->value;
}

string Wildcard::getArgumentType() {
	return this->argumentType;
}
