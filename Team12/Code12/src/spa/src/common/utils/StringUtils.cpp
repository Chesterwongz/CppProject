#include "StringUtils.h"

const char StringUtils::CHAR_NEWLINE = '\n';
const char StringUtils::CHAR_SPACE = ' ';
const char StringUtils::CHAR_ZERO = '0';
const string StringUtils::STRING_NEWLINE = "\n";

bool StringUtils::isNumeric(const string &str) {
    if (str.empty()) {
        return false;
    }
    return std::all_of(str.begin(), str.end(), [](const unsigned char c){ return std::isdigit(c); });
}

bool StringUtils::isName(const string &str) {
    if (str.empty() || !std::isalpha((unsigned char)str[0])) {
        return false;
    }
    return std::all_of(str.begin(), str.end(), [](const unsigned char c){ return std::isalnum(c); });
}

bool StringUtils::isInteger(const string &str) {
    if (str.length() > 1 && str[0] == CHAR_ZERO) {
        return false;
    }
    return isNumeric(str);
}

