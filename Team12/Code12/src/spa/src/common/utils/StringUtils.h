#pragma once

#include <algorithm>
#include <cctype>
#include <regex>
#include <string>

class StringUtils {
 public:
  static const char CHAR_ZERO;

  static bool isWhiteSpace(char ch);
  static bool isDigit(char ch);
  static bool isAlpha(char ch);
  static bool isAlphaNumeric(char ch);

 private:
  StringUtils() = default;
};
