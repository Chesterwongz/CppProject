#pragma once

#include <algorithm>
#include <cctype>
#include <regex>
#include <string>
#include <map>

using std::string;

// Define operator precedence
std::map<char, int> precedence = {
    {'(', 0}, {')', 0},
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2}
};

class QPSStringUtils {
public:
    static const string WILDCARD;

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
