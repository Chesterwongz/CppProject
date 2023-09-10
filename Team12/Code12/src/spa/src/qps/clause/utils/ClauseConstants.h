
#include <string>
#include "qps/token/suchThatToken/SuchThatToken.h"

using std::string, std::map;

// Statement types
typedef string StatementType;

const string ASSIGN_STMT_TYPE = "ASSIGN";
const string CALL_STMT_TYPE = "CALL";
const string IF_STMT_TYPE = "IF";
const string PRINT_STMT_TYPE = "PRINT";
const string READ_STMT_TYPE = "READ";
const string WHILE_STMT_TYPE = "WHILE";

const map<Entity, StatementType> EntityToStatementType = {
        {"Assign", ASSIGN_STMT_TYPE},
        {"Call", CALL_STMT_TYPE},
        {"If", IF_STMT_TYPE},
        {"Print", PRINT_STMT_TYPE},
        {"Read", READ_STMT_TYPE},
        {"While", WHILE_STMT_TYPE},
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



