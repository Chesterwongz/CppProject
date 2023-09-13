#include <string>

#include <../IArgument.h>
#include "Synonym.h"

string Synonym::getValue() {
	return this->value;
}

string Synonym::getArgumentType() {
	return this->argumentType;
}
