#include "QPSStringUtils.h"

#include "qps/common/Keywords.h"

using std::string;

map<char, int> QPSStringUtils::precedence = {
    {'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}};

bool QPSStringUtils::isSynonym(const string& data) {
  return std::isalpha(data[0]) &&
         std::all_of(data.begin(), data.end(),
                     [](unsigned char ch) { return std::isalnum(ch); });
}

bool QPSStringUtils::isIdent(const string& data) {
  return std::isalpha(data[0]) &&
         std::all_of(data.begin(), data.end(),
                     [](unsigned char ch) { return std::isalnum(ch); });
}

bool QPSStringUtils::isWildcard(string data) {
  return data == WILDCARD_KEYWORD;
}

bool QPSStringUtils::isInteger(string data) {
  string integerRegex;

  if (data.size() == 1) {
    integerRegex = "[0-9]";
  } else {
    integerRegex = "[1-9][0-9]+";
  }
  std::regex integerPattern(integerRegex);
  return std::regex_match(data, integerPattern);
}

// used chatgpt for the algo, just changed variable names
string QPSStringUtils::convertToRPN(string exp) {
  // shunting yard algo

  std::string rpnResult = " ";
  std::stack<char> operators;

  for (char token : exp) {
    if (std::isalnum(token)) {
      rpnResult += token;
    } else if (token == '(') {
      operators.push(token);
    } else if (token == ')') {
      while (!operators.empty() && operators.top() != '(') {
        rpnResult += " ";
        rpnResult += operators.top();
        operators.pop();
      }
      operators.pop();  // Discard '('
    } else if (precedence.find(token) != precedence.end()) {
      while (!operators.empty() &&
             precedence[operators.top()] >= precedence[token]) {
        rpnResult += " ";
        rpnResult += operators.top();
        operators.pop();
      }
      rpnResult += " ";
      operators.push(token);
    }
  }

  while (!operators.empty()) {
    rpnResult += " ";
    rpnResult += operators.top();
    operators.pop();
  }

  rpnResult += " ";

  return rpnResult;
}

bool QPSStringUtils::isNameTokenChar(const char ch) {
  return isalnum(ch) || ch == kAsterisks || ch == kHash;
}

bool QPSStringUtils::isNotQuoteEnd(const char ch) { return ch != '\"'; }

void QPSStringUtils::ltrim(string& s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

void QPSStringUtils::rtrim(string& s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

void QPSStringUtils::trimString(string& s) {
  rtrim(s);
  ltrim(s);
}
