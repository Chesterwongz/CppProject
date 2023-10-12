#include "PatternExp.h"

#include <string>

#include "qps/exceptions/QPSInvalidQueryException.h"
map<char, int> precedence = {{'(', 0}, {')', 0}, {'+', 1},
                                             {'-', 1}, {'*', 2}, {'/', 2}};

string PatternExp::myRPN(string exp) {
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

PatternExp::PatternExp(string argumentValue) {
  patternExpValue = myRPN(argumentValue);
}

string PatternExp::getValue() { return patternExpValue; }

QPSStringUtils::ArgumentType PatternExp::getArgumentType() {
  return argumentType;
}

bool PatternExp::isPatternExp() { return true; }

bool PatternExp::operator==(const AbstractArgument& other) const {
  const auto* otherPatternExp = dynamic_cast<const PatternExp*>(&other);
  if (!otherPatternExp) return false;

  return this->patternExpValue == otherPatternExp->patternExpValue;
}
