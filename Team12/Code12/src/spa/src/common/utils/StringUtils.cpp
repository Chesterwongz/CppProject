#include "StringUtils.h"

const char StringUtils::CHAR_ZERO = '0';

bool StringUtils::isWhiteSpace(const char ch) {
  return regex_search(std::string(1, ch), std::regex("[ \t\r\n\f]"));
}

bool StringUtils::isDigit(const char ch) { return std::isdigit(ch); }

bool StringUtils::isAlpha(const char ch) { return std::isalpha(ch); }

bool StringUtils::isAlphaNumeric(const char ch) { return std::isalnum(ch); }

std::string StringUtils::intToStrMapper(const int& val) {
  return std::to_string(val);
}
