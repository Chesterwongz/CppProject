#pragma once

#include <string>
#include <unordered_map>

enum class SpTokenType {
  NAME,  // Identifier tokens, aka names
  INT,   // Constant tokens, aka integers
  DELIM,
  TERM_OP,  // e.g., *, /, %
  EXPR_OP,  // e.g., +, -
  REL_OP,   // e.g., <, <=, >, >=, ==, !=
  COND_OP,  // e.g., !, &&, ||
};

class TokenTypeUtils {
 public:
  static std::string toString(SpTokenType tokenType) {
    switch (tokenType) {
      case SpTokenType::NAME:
        return "NAME";
      case SpTokenType::INT:
        return "INT";
      case SpTokenType::DELIM:
        return "DELIM";
      case SpTokenType::TERM_OP:
        return "TERM_OP";
      case SpTokenType::EXPR_OP:
        return "EXPR_OP";
      case SpTokenType::REL_OP:
        return "REL_OP";
      case SpTokenType::COND_OP:
        return "COND_OP";
      default:
        return "UNKNOWN";
    }
  }
};