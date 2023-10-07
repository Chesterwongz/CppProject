#pragma once

#include <string>

enum class TNodeType {
  TNODE_PROGRAM,
  TNODE_PROCEDURE,
  TNODE_STMT_LIST,

  TNODE_STMT,
  TNODE_READ,
  TNODE_PRINT,
  TNODE_CALL,
  TNODE_ASSIGN,
  TNODE_WHILE,
  TNODE_IF,

  TNODE_COND,
  TNODE_NOT,
  TNODE_AND,
  TNODE_OR,

  TNODE_REL,
  TNODE_EQ,
  TNODE_NEQ,
  TNODE_GT,
  TNODE_GTE,
  TNODE_LT,
  TNODE_LTE,

  TNODE_EXPR,
  TNODE_PLUS,
  TNODE_MINUS,

  TNODE_TERM,
  TNODE_TIMES,
  TNODE_DIV,
  TNODE_MOD,

  TNODE_FACTOR,
  TNODE_VAR,
  TNODE_CONST,
};

class TNodeTypeUtils {
 public:
  static std::string toString(TNodeType nodeType) {
    switch (nodeType) {
      case TNodeType::TNODE_PROGRAM:
        return "TNODE_PROGRAM";
      case TNodeType::TNODE_PROCEDURE:
        return "TNODE_PROCEDURE";
      case TNodeType::TNODE_STMT_LIST:
        return "TNODE_STMT_LIST";

      case TNodeType::TNODE_STMT:
        return "TNODE_STMT";
      case TNodeType::TNODE_READ:
        return "TNODE_READ";
      case TNodeType::TNODE_PRINT:
        return "TNODE_PRINT";
      case TNodeType::TNODE_CALL:
        return "TNODE_CALL";
      case TNodeType::TNODE_ASSIGN:
        return "TNODE_ASSIGN";
      case TNodeType::TNODE_WHILE:
        return "TNODE_WHILE";
      case TNodeType::TNODE_IF:
        return "TNODE_IF";

      case TNodeType::TNODE_COND:
        return "TNODE_COND";
      case TNodeType::TNODE_NOT:
        return "TNODE_NOT";
      case TNodeType::TNODE_AND:
        return "TNODE_AND";
      case TNodeType::TNODE_OR:
        return "TNODE_OR";

      case TNodeType::TNODE_REL:
        return "TNODE_REL";
      case TNodeType::TNODE_EQ:
        return "TNODE_EQ";
      case TNodeType::TNODE_NEQ:
        return "TNODE_NEQ";
      case TNodeType::TNODE_GT:
        return "TNODE_GT";
      case TNodeType::TNODE_GTE:
        return "TNODE_GTE";
      case TNodeType::TNODE_LT:
        return "TNODE_LT";
      case TNodeType::TNODE_LTE:
        return "TNODE_LTE";

      case TNodeType::TNODE_EXPR:
        return "TNODE_EXPR";
      case TNodeType::TNODE_PLUS:
        return "TNODE_PLUS";
      case TNodeType::TNODE_MINUS:
        return "TNODE_MINUS";

      case TNodeType::TNODE_TERM:
        return "TNODE_TERM";
      case TNodeType::TNODE_TIMES:
        return "TNODE_TIMES";
      case TNodeType::TNODE_DIV:
        return "TNODE_DIV";
      case TNodeType::TNODE_MOD:
        return "TNODE_MOD";

      case TNodeType::TNODE_FACTOR:
        return "TNODE_FACTOR";
      case TNodeType::TNODE_VAR:
        return "TNODE_VAR";
      case TNodeType::TNODE_CONST:
        return "TNODE_CONST";
      default:
        return "UNKNOWN";
    }
  }
};
