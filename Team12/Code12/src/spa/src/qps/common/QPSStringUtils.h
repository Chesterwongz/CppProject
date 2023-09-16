#pragma once

#include <algorithm>
#include <cctype>
#include <regex>
#include <string>

using std::string;

class QPSStringUtils {
public:
    static const string WILDCARD;

    static bool isSynonym(const string data);
    static bool isStmtRef(const string data);
    static bool isEntRef(const string data);
    static bool isIdent(const string data);
    static bool isWildcard(const string data);
    static bool isInteger(const string data);

private:
    QPSStringUtils() = default;

};
