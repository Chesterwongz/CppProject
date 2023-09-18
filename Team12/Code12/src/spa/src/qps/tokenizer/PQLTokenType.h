#pragma once

#include <unordered_map>

// should encompass all available characters
// first char in buffer determines token type. 
// E.g. stmt s1; --> [PQL_NAME_TOKEN, PQL_NAME_TOKEN]

enum PQLTokenType {
    // for the first token
    PQL_NULL_TOKEN,

    // for synonyms and keywords.
    PQL_NAME_TOKEN,

    // for char
    PQL_CHAR_TOKEN,
    // for line numbers
    PQL_INTEGER_TOKEN,

    PQL_WILDCARD_TOKEN,

    // for whitespaces, enter and tab
    PQL_IGNORE_TOKEN,
 
    PQL_SEMICOLON_TOKEN,
    PQL_COMMA_TOKEN,
    PQL_PERIOD_TOKEN,
    PQL_ASTERICKS_TOKEN,

    // literals and arguments
    PQL_OPEN_BRACKET_TOKEN,
    PQL_CLOSE_BRACKET_TOKEN,
    PQL_QUOTE_TOKEN,

    // for operators in expressions for patterns
    PQL_OPERATOR_TOKEN,

    // should throw error if encountered
    PQL_INVALID_TOKEN,

    // more detailed states after going through the parser
    // main usage for predictive parser map

    // Declarative
    PQL_ENTITY_TOKEN,
    PQL_SYNONYM_TOKEN,

    // Select
    PQL_SELECT_TOKEN,

    // Such That
    PQL_FOLLOWS_TOKEN,
    PQL_PARENT_TOKEN,
    PQL_USES_TOKEN,
    PQL_MODIFIES_TOKEN,

    // Pattern
    PQL_PATTERN_TOKEN,
    PQL_LEFT_WILDCARD,
    PQL_RIGHT_WILDCARD
};

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

    { "Select", PQL_SELECT_TOKEN }
}

