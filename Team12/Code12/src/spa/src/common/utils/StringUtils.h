#pragma once

#include <algorithm>
#include <cctype>
#include <regex>
#include <string>

using std::string;

class StringUtils {
public:
    static const char CHAR_ZERO;
    static const string WILDCARD;

    static bool isWhiteSpace(char ch);
    static bool isDigit(char ch);
    static bool isAlpha(char ch);
    static bool isAlphaNumeric(char ch);

    static bool isSynonym(const string data);
    static bool isStmtRef(const string data);
    static bool isEntRef(const string data);
    static bool isIdent(const string data);
    static bool isWildcard(const string data);

private:
    StringUtils() = default;

};
