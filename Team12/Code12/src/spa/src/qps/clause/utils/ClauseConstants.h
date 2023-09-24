#pragma once

#include <string>
#include <unordered_map>

using std::string, std::unordered_map;

const unordered_map<Entity, StmtType> EntityToStatementType = {
        {"assign", StmtType::ASSIGN},
        {"call", StmtType::CALL},
        {"if", StmtType::IF},
        {"print", StmtType::PRINT},
        {"read", StmtType::READ},
        {"while", StmtType::WHILE},
        {"stmt", StmtType::STMT},
};

// Abstractions
enum Abstraction {
    FOLLOWS_ENUM,
    MODIFIES_ENUM,
    PARENTS_ENUM,
    USES_ENUM,
};
