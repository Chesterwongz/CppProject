#pragma once

#include <string>
#include <unordered_set>
#include <vector>

using std::string, std::vector, std::unordered_set;

typedef string Synonym;
typedef string Entity;
typedef string AttrRef;

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

inline const Entity INVALID_ENTITY = "INVALID";

inline const string BOOLEAN_KEYWORD = "BOOLEAN";

inline const string NOT_KEYWORD = "not";

inline const string SELECT_KEYWORD = "Select";
inline const string SUCH_KEYWORD = "such";
inline const string THAT_KEYWORD = "that";
inline const string PATTERN_KEYWORD = "pattern";

inline const string AND_KEYWORD = "and";

inline const string FOLLOWS_ABSTRACTION = "Follows";
inline const string FOLLOWS_STAR_ABSTRACTION = "Follows*";
inline const string MODIFIES_ABSTRACTION = "Modifies";
inline const string PARENTS_ABSTRACTION = "Parent";
inline const string PARENTS_STAR_ABSTRACTION = "Parent*";
inline const string NEXT_ABSTRACTION = "Next";
inline const string NEXT_STAR_ABSTRACTION = "Next*";
inline const string AFFECTS_ABSTRACTION = "Affects";
inline const string USES_ABSTRACTION = "Uses";
inline const string CALLS_ABSTRACTION = "Calls";
inline const string CALLS_STAR_ABSTRACTION = "Calls*";

inline const string WITH_KEYWORD = "with";

inline const AttrRef ATTR_REF_DEFAULT =
    "";  // for synonyms without attrRef specified
inline const AttrRef ATTR_REF_PROC_NAME = "procName";
inline const AttrRef ATTR_REF_STMT_NUMBER = "stmt#";
inline const AttrRef ATTR_REF_VAR_NAME = "varName";
inline const AttrRef ATTR_REF_VALUE = "value";

inline const AttrRef ATTR_REF_INVALID = "invalid";

inline const string WILDCARD_KEYWORD = "_";
inline const string INVALID_STATEMENT_NUMBER = "-1";

namespace pqlDelim {
constexpr char kSemicolonChar = ';';
constexpr char kCommaChar = ',';
constexpr char kQuoteChar = '\"';
constexpr char kOpenBracketChar = '(';
constexpr char kCloseBracketChar = ')';
constexpr char kWildcardChar = '_';
constexpr char kLeftAngleChar = '<';
constexpr char kRightAngleChar = '>';
constexpr char kPeriodChar = '.';
constexpr char kEqualChar = '=';
}  // namespace pqlDelim

inline const unordered_set<string> STATEMENT_ENTITIES = {
    ASSIGN_ENTITY, CALL_ENTITY, IF_ENTITY,    PRINT_ENTITY,
    READ_ENTITY,   STMT_ENTITY, WHILE_ENTITY,
};
