#pragma once

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
    TNODE_VAR,
    TNODE_CONST,
    TNODE_NOT,
    TNODE_AND,
    TNODE_OR,
    TNODE_EQ,
    TNODE_NEQ,
    TNODE_GT,
    TNODE_GTE,
    TNODE_LT,
    TNODE_LTE,
    TNODE_PLUS,
    TNODE_MINUS,
    TNODE_TIMES,
    TNODE_DIV,
    TNODE_MOD,
};