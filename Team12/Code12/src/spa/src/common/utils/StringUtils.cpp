#include "StringUtils.h"

#include "CollectionUtils.h"

const char StringUtils::CHAR_ZERO = '0';

bool StringUtils::isWhiteSpace(const char ch) {
  return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\f';
}

bool StringUtils::isDigit(const char ch) { return std::isdigit(ch); }

bool StringUtils::isAlpha(const char ch) { return std::isalpha(ch); }

bool StringUtils::isAlphaNumeric(const char ch) { return std::isalnum(ch); }
