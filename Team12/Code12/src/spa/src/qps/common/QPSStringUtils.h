#pragma once

#include <algorithm>
#include <cctype>
#include <map>
#include <regex>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>

#include "common/utils/StringUtils.h"

using std::string, std::map;

class QPSStringUtils {
 public:
  static map<char, int> precedence;
  static constexpr char kAsterisks = '*';
  static constexpr char kHash = '#';

  enum ArgumentType { IDENT, SYNONYM, WILDCARD, INTEGER, PATTERNEXP };

  inline const static std::unordered_map<QPSStringUtils::ArgumentType, string>
      ArgTypeToKeyMap = {
          {QPSStringUtils::ArgumentType::IDENT, "IDENT"},
          {QPSStringUtils::ArgumentType::SYNONYM, "SYNONYM"},
          {QPSStringUtils::ArgumentType::WILDCARD, "WILDCARD"},
          {QPSStringUtils::ArgumentType::INTEGER, "INTEGER"},
          {QPSStringUtils::ArgumentType::PATTERNEXP, "PATTERNEXP"},
  };

  static bool isSynonym(const string& data);
  static bool isIdent(const string& data);
  static bool isWildcard(const string& data);
  static bool isInteger(string data);
  static bool isNameTokenChar(char ch);
  static bool isNotQuoteEnd(char ch);
  static void trimString(string& s);
  static string convertToRPN(const string& exp);

 private:
  static void ltrim(string& s);
  static void rtrim(string& s);
  QPSStringUtils() = default;
};
