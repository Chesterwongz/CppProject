#include <stack>
#include "QPSStringUtils.h"

using std::string;

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
