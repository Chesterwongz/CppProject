#pragma once

#include <string>
#include <unordered_map>
#include "qps/common/Keywords.h"

using std::string, std::unordered_map;

const unordered_map<Entity, StmtType> StmtEntityToStatementType = {
        {ASSIGN_ENTITY, StmtType::ASSIGN},
        {CALL_ENTITY, StmtType::CALL},
        {IF_ENTITY, StmtType::IF},
        {PRINT_ENTITY, StmtType::PRINT},
        {READ_ENTITY, StmtType::READ},
        {WHILE_ENTITY, StmtType::WHILE},
        {STMT_ENTITY, StmtType::STMT},
};

// Abstractions
enum Abstraction {
    FOLLOWS_ENUM,
    FOLLOWS_STAR_ENUM,
    MODIFIES_ENUM,
    PARENTS_ENUM,
    PARENTS_STAR_ENUM,
    USES_ENUM,
};
