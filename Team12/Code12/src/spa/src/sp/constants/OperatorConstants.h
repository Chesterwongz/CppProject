#pragma once

#include <string>

using std::string;

namespace op {
constexpr char kNotChar = '!';
constexpr char kEqChar = '=';
constexpr char kAndChar = '&';
constexpr char kOrChar = '|';
constexpr char kLtChar = '<';
constexpr char kGtChar = '>';
constexpr char kMinusChar = '-';
constexpr char kPlusChar = '+';
constexpr char kTimesChar = '*';
constexpr char kDivChar = '/';
constexpr char kModChar = '%';

// Arithmetic op
const string kPlus = "+";
const string kMinus = "-";
const string kTimes = "*";
const string kDiv = "/";
const string kMod = "%";

// Conditional op
const string kNot = "!";
const string kAnd = "&&";
const string kOr = "||";

// Relational op
const string kNeq = "!=";
const string kEq = "==";
const string kLt = "<";
const string kLte = "<=";
const string kGt = ">";
const string kGte = ">=";

}  // namespace op
