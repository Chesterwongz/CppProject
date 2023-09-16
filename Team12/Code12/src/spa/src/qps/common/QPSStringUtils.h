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
    static string convertToRPN(string exp);
private:
    QPSStringUtils() = default;

};
