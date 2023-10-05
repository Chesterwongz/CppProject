#include "StringUtils.h"

using std::string;

const char StringUtils::CHAR_ZERO = '0';

bool StringUtils::isWhiteSpace(const char ch) {
  return regex_search(std::string(1, ch), std::regex("[ \t\r\n\f]"));
}

bool StringUtils::isDigit(const char ch) { return std::isdigit(ch); }

bool StringUtils::isAlpha(const char ch) { return std::isalpha(ch); }

bool StringUtils::isAlphaNumeric(const char ch) { return std::isalnum(ch); }
