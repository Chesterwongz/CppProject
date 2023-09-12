#pragma once

#include <string>
#include <unordered_map>

enum class TokenType {
    NAME, // Identifier tokens, aka names
    OP, // op tokens, e.g., ">"
    INT, // Constant tokens, aka integers
    DELIM,
    TERM_OP, // e.g., *, /, %
    EXPR_OP, // e.g., +, -
    REL_OP, // e.g., <, <=, >, >=, ==, !=
    COND_OP, // e.g., !, &&, ||
};

class TokenTypeUtils {
public:
    static std::string toString(TokenType tokenType) {
        switch (tokenType){
            case TokenType::NAME:
                return "NAME";
            case TokenType::OP:
                return "OP";
            case TokenType::INT:
                return "INT";
            case TokenType::DELIM:
                return "DELIM";
            case TokenType::TERM_OP:
                return "TERM_OP";
            case TokenType::EXPR_OP:
                return "EXPR_OP";
            case TokenType::REL_OP:
                return "REL_OP";
            case TokenType::COND_OP:
                return "COND_OP";
            default:
                return "UNKNOWN";
        }
    }
};