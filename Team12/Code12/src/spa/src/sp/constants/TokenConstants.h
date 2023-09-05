#include <string_view>

/*
 * Concrete Syntax Grammar tokens for the SIMPLE programming language
 * https://nus-cs3203.github.io/course-website/contents/basic-spa-requirements/simple-programming.html#simple-programming-language
*/

using std::string_view;

namespace tokens {

    constexpr string_view PROCEDURE = "procedure";

    constexpr string_view OPEN_BRACKETS = "(";
    constexpr string_view CLOSE_BRACKETS = ")";
    constexpr string_view OPEN_CURLY = "{";
    constexpr string_view CLOSE_CURLY = "}";
    constexpr string_view SEMI_COLO = ";";

    // stmt keywords
    constexpr string_view READ = "read";
    constexpr string_view PRINT = "print";
    constexpr string_view CALL = "call";
    constexpr string_view IF = "if";
    constexpr string_view THEN = "then";
    constexpr string_view ELSE = "else";
    constexpr string_view ASSIGN = "=";

    // conditional expressions
    constexpr string_view NOT = "!";
    constexpr string_view AND = "&&";
    constexpr string_view OR = "||";

    // relational expressions
    constexpr string_view GT = ">";
    constexpr string_view GTE = ">=";
    constexpr string_view LT = "<";
    constexpr string_view LTE = "<=";
    constexpr string_view EQ = "==";
    constexpr string_view NEQ = "!=";

    // mathematical expressions
    constexpr string_view ADDITION = "+";
    constexpr string_view SUBTRACTION = "-";
    constexpr string_view MULTIPLICATION = "*";
    constexpr string_view DIVISION = "/";
    constexpr string_view MODULO = "%";

}
