#include <string>

#include "../IArgument.h"
#include "Synonym.h"

string Synonym::getValue() {
	return synonymValue;
}

string Synonym::getArgumentType() {
	return argumentType;
}
