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
