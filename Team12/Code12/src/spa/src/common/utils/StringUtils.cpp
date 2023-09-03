#include "StringUtils.h"

const char StringUtils::CHAR_ZERO = '0';

bool StringUtils::isWhiteSpace(const char ch) {
    return regex_search(std::string(1, ch), std::regex("[ \t\r\n\f]"));
}

bool StringUtils::isDigit(char ch) {
    return std::isdigit(ch);
}

bool StringUtils::isAlpha(char ch) {
    return std::isalpha(ch);
}

bool StringUtils::isAlphaNumeric(char ch) {
    return std::isalnum(ch);
}
