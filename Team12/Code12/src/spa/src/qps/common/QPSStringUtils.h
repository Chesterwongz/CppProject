#pragma once

#include <algorithm>
#include <cctype>
#include <map>
#include <regex>
#include <stack>
#include <string>

#include "common/utils/StringUtils.h"

using std::string, std::map;

class QPSStringUtils {
 private:
  static bool isCharExpression(char ch);
 public:
  static map<char, int> precedence;

  enum ArgumentType { IDENT, SYNONYM, WILDCARD, INTEGER };

  static bool isSynonym(const string data);
  static bool isStmtRef(const string data);
  static bool isEntRef(const string data);
  static bool isIdent(const string data);
  static bool isIdentValue(const string& data);
  static bool isWildcard(const string data);
  static bool isInteger(const string data);
  static bool isValidExpression(const string& data);
  static string convertToRPN(string exp);

 private:
  QPSStringUtils() = default;
};
