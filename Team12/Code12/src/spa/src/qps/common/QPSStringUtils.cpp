#include "QPSStringUtils.h"

using std::string;

const string QPSStringUtils::WILDCARD = "_";

bool QPSStringUtils::isSynonym(string data) {
    std::regex synonymPattern("^[A-Za-z][A-Za-z0-9]*$");
    return std::regex_match(data, synonymPattern);
}

bool QPSStringUtils::isStmtRef(string data) {
    return isSynonym(data) || isWildcard(data) || isInteger(data);
}

bool QPSStringUtils::isEntRef(string data) {
    return isSynonym(data) || isWildcard(data) || isIdent(data);
}

bool QPSStringUtils::isIdent(string data) {
    std::regex identQuotePattern("\"[A-Za-z]([A-Za-z0-9])*\"");

    return std::regex_match(data, identQuotePattern);
}

bool QPSStringUtils::isWildcard(string data) {
    return data == WILDCARD;
}

bool QPSStringUtils::isInteger(string data) {
    std::regex integerPattern("^[0-9]+$");
    return std::regex_match(data, integerPattern);
}