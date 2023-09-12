#pragma once

#include <string>
#include <map>
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "qps/token/declarativeToken/DeclarativeToken.h"

using std::string, std::map;

// Statement types
typedef string StatementType;

const string ASSIGN_STMT_TYPE = "ASSIGN";
const string CALL_STMT_TYPE = "CALL";
const string IF_STMT_TYPE = "IF";
const string PRINT_STMT_TYPE = "PRINT";
const string READ_STMT_TYPE = "READ";
const string WHILE_STMT_TYPE = "WHILE";
const string STMT_TYPE = "STMT";

const map<Entity, StatementType> EntityToStatementType = {
        {"assign", ASSIGN_STMT_TYPE},
        {"call", CALL_STMT_TYPE},
        {"if", IF_STMT_TYPE},
        {"print", PRINT_STMT_TYPE},
        {"read", READ_STMT_TYPE},
        {"while", WHILE_STMT_TYPE},
        {"stmt", STMT_TYPE},
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
