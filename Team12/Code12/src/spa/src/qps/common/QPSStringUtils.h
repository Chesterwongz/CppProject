#pragma once

#include <algorithm>
#include <cctype>
#include <regex>
#include <string>
#include <map>
#include <stack>

#include "common/utils/StringUtils.h"

using std::string, std::map;

class QPSStringUtils {
public:
    static map<char, int> precedence;

    enum ArgumentType {
        IDENT,
        SYNONYM,
        WILDCARD,
        INTEGER
    };

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
