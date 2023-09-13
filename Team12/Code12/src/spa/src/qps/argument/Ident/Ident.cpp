#include <string>

#include <../IArgument.h>
#include "Ident.h"

string Ident::getValue() {
	return this->value;
}

string Ident::getArgumentType() {
	return this->argumentType;
}
