#include <string>

#include "../IArgument.h"
#include "Ident.h"

string Ident::getValue() {
	return identValue;
}

string Ident::getArgumentType() {
	return argumentType;
}
