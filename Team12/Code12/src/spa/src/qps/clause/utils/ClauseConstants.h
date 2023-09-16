#pragma once

#include <string>
#include <map>
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/token/declarativeToken/DeclarativeToken.h"

using std::string, std::map;

// Statement types
const map<Entity, StmtType> EntityToStatementType = {
        {"assign", StmtType::ASSIGN},
        {"call", StmtType::CALL},
        {"if", StmtType::IF},
        {"print", StmtType::PRINT},
        {"read", StmtType::READ},
        {"while", StmtType::WHILE},
        {"stmt", StmtType::STMT},
};

// Abstractions
enum AbstractionEnum {
    FOLLOWS_ENUM,
    MODIFIES_ENUM,
    PARENTS_ENUM,
    USES_ENUM,
};

const Abstraction FOLLOWS = "Follows";
const Abstraction MODIFIES = "Modifies";
const Abstraction PARENTS = "Parents";
const Abstraction USES = "Uses";

const map<Abstraction, AbstractionEnum> AbstractionToEnumMap = {
        {"FOLLOWS", FOLLOWS_ENUM},
        {"MODIFIES", MODIFIES_ENUM},
        {"PARENTS", PARENTS_ENUM},
        {"USES", USES_ENUM},
};
