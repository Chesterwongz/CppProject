#include "PQLParserUtils.h"

bool PQLParserUtils::isValidName(string data) {
	regex synonymPattern("^[A-Za-z][A-Za-z0-9]*$");
	return regex_match(data, synonymPattern);
}

bool PQLParserUtils::isValidInteger(string data) {
	regex integerPattern("^[1-9][0-9]*$");
	return regex_match(data, integerPattern);
}

bool PQLParserUtils::isSynonym(string data) {
	return isValidName(data);
}

bool PQLParserUtils::isStmtRef(string data) {
	return isSynonym(data) || data == "_" || isValidInteger(data);
}

bool PQLParserUtils::isEntRef(string data) {
	// this pattern is to check for '"' IDENT '"'
	regex identQuotePattern("\"[A-Za-z]([A-Za-z0-9])*\"");

	return isSynonym(data) || data == "_" || std::regex_match(data, identQuotePattern);
}
