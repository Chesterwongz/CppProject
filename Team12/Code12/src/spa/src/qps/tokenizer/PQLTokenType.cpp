#include "PQLTokenType.h"
#include "qps/common/Keywords.h"

unordered_map<string, PQLTokenType> keywordToTokenType = {
        { STMT_ENTITY, PQL_ENTITY_TOKEN },
        { READ_ENTITY, PQL_ENTITY_TOKEN },
        { PRINT_ENTITY, PQL_ENTITY_TOKEN },
        { CALL_ENTITY, PQL_ENTITY_TOKEN },
        { WHILE_ENTITY, PQL_ENTITY_TOKEN },
        { IF_ENTITY, PQL_ENTITY_TOKEN },
        { ASSIGN_ENTITY, PQL_ENTITY_TOKEN },
        { VARIABLE_ENTITY, PQL_ENTITY_TOKEN },
        { CONSTANT_ENTITY, PQL_ENTITY_TOKEN },
        { PROCEDURE_ENTITY, PQL_ENTITY_TOKEN },

        { SELECT_KEYWORD, PQL_SELECT_TOKEN },

        { SUCH_KEYWORD, PQL_SUCH_TOKEN },
        { THAT_KEYWORD, PQL_THAT_TOKEN },
        { FOLLOWS_ABSTRACTION, PQL_FOLLOWS_TOKEN },
        { PARENTS_ABSTRACTION, PQL_PARENT_TOKEN },
        { USES_ABSTRACTION, PQL_USES_TOKEN },
        { MODIFIES_ABSTRACTION, PQL_MODIFIES_TOKEN },

        { PATTERN_KEYWORD, PQL_PATTERN_TOKEN}
};

unordered_set<PQLTokenType> delimiterTokens = {
        PQL_IGNORE_TOKEN,
        PQL_SEMICOLON_TOKEN,
        PQL_COMMA_TOKEN,
        PQL_QUOTE_TOKEN,
        PQL_OPEN_BRACKET_TOKEN,
        PQL_CLOSE_BRACKET_TOKEN,
        PQL_ASTERISKS_TOKEN,
        PQL_WILDCARD_TOKEN,
        PQL_OPERATOR_TOKEN
};

unordered_set<string> stmtEntities = {
        STMT_ENTITY,
        READ_ENTITY,
        PRINT_ENTITY,
        ASSIGN_ENTITY,
        CALL_ENTITY,
        WHILE_ENTITY,
        IF_ENTITY
};
