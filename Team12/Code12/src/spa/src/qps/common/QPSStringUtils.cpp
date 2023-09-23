#include "QPSStringUtils.h"

using std::string;

map<char, int> QPSStringUtils::precedence = {
    {'(', 0}, {')', 0},
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2}
};

bool QPSStringUtils::isSynonym(string data) {
    std::regex synonymPattern("^[A-Za-z][A-Za-z0-9]*$");
    return std::regex_match(data, synonymPattern);
}

bool QPSStringUtils::isStmtRef(string data) {
    return isSynonym(data) || isWildcard(data) || isInteger(data);
}

bool QPSStringUtils::isEntRef(string data) {
    return isSynonym(data) || isWildcard(data) || isIdent(data);
}

bool QPSStringUtils::isIdent(string data) {
    std::regex identQuotePattern("\"[A-Za-z]([A-Za-z0-9])*\"");

    return std::regex_match(data, identQuotePattern);
}

bool QPSStringUtils::isWildcard(string data) {
    return data == StringUtils::WILDCARD;
}

bool QPSStringUtils::isInteger(string data) {

    string integerRegex;

    if (data.size() == 1) {
        integerRegex = "[0-9]";
    }
    else {
        integerRegex = "[1-9][0-9]+";
        
    }
    std::regex integerPattern(integerRegex);
    return std::regex_match(data, integerPattern);
}

// used chat gpt for the algo, just changed variable names
string QPSStringUtils::convertToRPN(string exp) {
    //shunting yard algo

    std::string rpnResult;
    std::stack<char> operators;

    for (char token : exp) {
        if (isdigit(token)) {
            rpnResult += token;
        }
        else if (token == '(') {
            operators.push(token);
        }
        else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                rpnResult += operators.top();
                operators.pop();
            }
            operators.pop(); // Discard '('
        }
        else if (precedence.find(token) != precedence.end()) {
            while (!operators.empty() && precedence[operators.top()] >= precedence[token]) {
                rpnResult += operators.top();
                operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        rpnResult += operators.top();
        operators.pop();
    }

    return rpnResult;
}
