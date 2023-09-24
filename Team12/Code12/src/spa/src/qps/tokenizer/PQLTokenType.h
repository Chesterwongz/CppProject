#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

using std::unordered_map, std::string, std::unordered_set;

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
    PQL_ASTERISKS_TOKEN,

    // literals and arguments
    PQL_OPEN_BRACKET_TOKEN,
    PQL_CLOSE_BRACKET_TOKEN,
    PQL_QUOTE_TOKEN,
    PQL_LITERAL_EXPRESSION_TOKEN,
    PQL_LITERAL_REF_TOKEN,

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
    PQL_SUCH_TOKEN,
    PQL_THAT_TOKEN,
    PQL_FOLLOWS_TOKEN,
    PQL_PARENT_TOKEN,
    PQL_USES_TOKEN,
    PQL_MODIFIES_TOKEN,

    // Pattern
    PQL_PATTERN_TOKEN,
};

extern unordered_map<string, PQLTokenType> keywordToTokenType;
extern unordered_set<PQLTokenType> delimiterTokens;
extern unordered_set<string> stmtEntities;
