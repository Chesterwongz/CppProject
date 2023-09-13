#pragma once

#include <string>

using std::string;

class ArgumentFactoryUtil {
public:
    static const string wildcard = "_";
    static const char doublequotes = '"';

    static bool isSynonym(string argument);
    static bool isIdent(string argument);
    static bool isWildcard(string argument);
};