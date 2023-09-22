#include "PQLTokenType.h"

unordered_map<string, PQLTokenType> keywordToTokenType = {
        { "stmt", PQL_ENTITY_TOKEN },
        { "read", PQL_ENTITY_TOKEN },
        { "print", PQL_ENTITY_TOKEN },
        { "call", PQL_ENTITY_TOKEN },
        { "while", PQL_ENTITY_TOKEN },
        { "if", PQL_ENTITY_TOKEN },
        { "assign", PQL_ENTITY_TOKEN },
        { "variable", PQL_ENTITY_TOKEN },
        { "constant", PQL_ENTITY_TOKEN },
        { "procedure", PQL_ENTITY_TOKEN },

        { "Select", PQL_SELECT_TOKEN },

        { "such", PQL_SUCH_TOKEN },
        { "that", PQL_THAT_TOKEN }
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
