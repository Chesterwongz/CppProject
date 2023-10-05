#pragma once

#include <string>
#include <unordered_set>
#include <vector>

using std::string, std::vector, std::unordered_set;

typedef string Entity;

inline const Entity ASSIGN_ENTITY = "assign";
inline const Entity CALL_ENTITY = "call";
inline const Entity CONSTANT_ENTITY = "constant";
inline const Entity IF_ENTITY = "if";
inline const Entity PRINT_ENTITY = "print";
inline const Entity PROCEDURE_ENTITY = "procedure";
inline const Entity READ_ENTITY = "read";
inline const Entity STMT_ENTITY = "stmt";
inline const Entity VARIABLE_ENTITY = "variable";
inline const Entity WHILE_ENTITY = "while";

inline const string SELECT_KEYWORD = "Select";
inline const string SUCH_KEYWORD = "such";
inline const string THAT_KEYWORD = "that";
inline const string PATTERN_KEYWORD = "pattern";

inline const string FOLLOWS_ABSTRACTION = "Follows";
inline const string MODIFIES_ABSTRACTION = "Modifies";
inline const string PARENTS_ABSTRACTION = "Parent";
inline const string USES_ABSTRACTION = "Uses";

inline const string WILDCARD_KEYWORD = "_";
inline const string INVALID_STATEMENT_NUMBER = "-1";

inline const unordered_set<string> STATEMENT_ENTITIES = {
        ASSIGN_ENTITY,
        CALL_ENTITY,
        IF_ENTITY,
        PRINT_ENTITY,
        READ_ENTITY,
        STMT_ENTITY,
        WHILE_ENTITY,
};
