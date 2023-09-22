#pragma once

#include <algorithm>
#include <cctype>
#include <regex>
#include <string>
#include <map>
#include <stack>

using std::string, std::map;

class QPSStringUtils {
public:
    static const string WILDCARD;
    static map<char, int> precedence;

    static bool isSynonym(const string data);
    static bool isStmtRef(const string data);
    static bool isEntRef(const string data);
    static bool isIdent(const string data);
    static bool isWildcard(const string data);
    static bool isInteger(const string data);
    static string convertToRPN(string exp);
private:
    QPSStringUtils() = default;

};
