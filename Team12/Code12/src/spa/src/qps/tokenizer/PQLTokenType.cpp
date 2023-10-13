#include "PQLTokenType.h"

unordered_map<string, PQLTokenType> keywordToTokenType = {
    {STMT_ENTITY, PQL_ENTITY_TOKEN},
    {READ_ENTITY, PQL_ENTITY_TOKEN},
    {PRINT_ENTITY, PQL_ENTITY_TOKEN},
    {CALL_ENTITY, PQL_ENTITY_TOKEN},
    {WHILE_ENTITY, PQL_ENTITY_TOKEN},
    {IF_ENTITY, PQL_ENTITY_TOKEN},
    {ASSIGN_ENTITY, PQL_ENTITY_TOKEN},
    {VARIABLE_ENTITY, PQL_ENTITY_TOKEN},
    {CONSTANT_ENTITY, PQL_ENTITY_TOKEN},
    {PROCEDURE_ENTITY, PQL_ENTITY_TOKEN},

    {SELECT_KEYWORD, PQL_SELECT_TOKEN},

    {BOOLEAN_KEYWORD, PQL_BOOLEAN_TOKEN},

    {AND_KEYWORD, PQL_AND_TOKEN},

    {SUCH_KEYWORD, PQL_SUCH_TOKEN},
    {THAT_KEYWORD, PQL_THAT_TOKEN},
    {FOLLOWS_ABSTRACTION, PQL_STMT_STMT_TOKEN},
    {FOLLOWS_STAR_ABSTRACTION, PQL_STMT_STMT_TOKEN},
    {PARENTS_ABSTRACTION, PQL_STMT_STMT_TOKEN},
    {PARENTS_STAR_ABSTRACTION, PQL_STMT_STMT_TOKEN},
    {NEXT_ABSTRACTION, PQL_STMT_STMT_TOKEN},
    {NEXT_STAR_ABSTRACTION, PQL_STMT_STMT_TOKEN},
    {AFFECTS_ABSTRACTION, PQL_STMT_STMT_TOKEN},
    {USES_ABSTRACTION, PQL_STMT_VAR_TOKEN},
    {MODIFIES_ABSTRACTION, PQL_STMT_VAR_TOKEN},
    {CALLS_ABSTRACTION, PQL_PROC_PROC_TOKEN},
    {CALLS_STAR_ABSTRACTION, PQL_PROC_PROC_TOKEN},

    {PATTERN_KEYWORD, PQL_PATTERN_TOKEN}};

unordered_map<char, PQLTokenType> delimiterToTokenType = {
    {pqlDelim::kSemicolonChar, PQL_SEMICOLON_TOKEN},
    {pqlDelim::kCommaChar, PQL_COMMA_TOKEN},
    {pqlDelim::kWildcardChar, PQL_WILDCARD_TOKEN},
    {pqlDelim::kOpenBracketChar, PQL_OPEN_BRACKET_TOKEN},
    {pqlDelim::kCloseBracketChar, PQL_CLOSE_BRACKET_TOKEN},
    {pqlDelim::kLeftAngleChar, PQL_LEFT_ANGLE_TOKEN},
    {pqlDelim::kRightAngleChar, PQL_RIGHT_ANGLE_TOKEN},
    {pqlDelim::kPeriodChar, PQL_PERIOD_TOKEN},
    {pqlDelim::kEqualChar, PQL_EQUALS_TOKEN}};

unordered_set<string> stmtEntities = {STMT_ENTITY,   READ_ENTITY, PRINT_ENTITY,
                                      ASSIGN_ENTITY, CALL_ENTITY, WHILE_ENTITY,
                                      IF_ENTITY};
