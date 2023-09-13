#include "StringUtils.h"

using std::string;

const char StringUtils::CHAR_ZERO = '0';
const string StringUtils::wildcard = "_";

bool StringUtils::isWhiteSpace(const char ch) {
    return regex_search(std::string(1, ch), std::regex("[ \t\r\n\f]"));
}

bool StringUtils::isDigit(const char ch) {
    return std::isdigit(ch);
}

bool StringUtils::isAlpha(const char ch) {
    return std::isalpha(ch);
}

bool StringUtils::isAlphaNumeric(const char ch) {
    return std::isalnum(ch);
}

bool StringUtils::isSynonym(string data) {
    std::regex synonymPattern("^[A-Za-z][A-Za-z0-9]*$");
    return std::regex_match(data, synonymPattern);
}

bool StringUtils::isStmtRef(string data) {
    std::regex integerPattern("^[0-9]+$");
    return isSynonym(data) || isWildcard(data) || std::regex_match(data, integerPattern);
}

bool StringUtils::isEntRef(string data) {
    // this pattern is to check for '"' IDENT '"'
    std::regex identQuotePattern("\"[A-Za-z]([A-Za-z0-9])*\"");

    return isSynonym(data) || isWildcard(data) || isIdent(data);
}

bool StringUtils::isIdent(string data) {
    std::regex identQuotePattern("\"[A-Za-z]([A-Za-z0-9])*\"");

    return std::regex_match(data, identQuotePattern);
}

bool StringUtils::isWildcard(string data) {
    return data == wildcard;
}
