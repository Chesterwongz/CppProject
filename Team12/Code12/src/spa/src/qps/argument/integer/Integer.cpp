#include <string>

#include "../IArgument.h"
#include "Integer.h"

string Integer::getValue() {
	return integerValue;
}

string Integer::getArgumentType() {
	return argumentType;
}
