#pragma once

#include <string>
#include <unordered_set>
#include <vector>

using std::string, std::vector, std::unordered_set;

typedef string Synonym;
typedef string Entity;

inline const string ASSIGN_ENTITY = "assign";
inline const string CALL_ENTITY = "call";
inline const string CONSTANT_ENTITY = "constant";
inline const string IF_ENTITY = "if";
inline const string PRINT_ENTITY = "print";
inline const string PROCEDURE_ENTITY = "procedure";
inline const string READ_ENTITY = "read";
inline const string STMT_ENTITY = "stmt";
inline const string VARIABLE_ENTITY = "variable";
inline const string WHILE_ENTITY = "while";

inline const string SELECT_KEYWORD = "Select";
inline const string SUCH_KEYWORD = "such";
inline const string THAT_KEYWORD = "that";
inline const string PATTERN_KEYWORD = "pattern";

inline const string FOLLOWS_ABSTRACTION = "Follows";
inline const string FOLLOWS_STAR_ABSTRACTION = "Follows*";
inline const string MODIFIES_ABSTRACTION = "Modifies";
inline const string PARENTS_ABSTRACTION = "Parent";
inline const string PARENTS_STAR_ABSTRACTION = "Parent*";
inline const string NEXT_ABSTRACTION = "Next";
inline const string NEXT_STAR_ABSTRACTION = "Next*";
inline const string USES_ABSTRACTION = "Uses";
inline const string CALLS_ABSTRACTION = "Calls";
inline const string CALLS_STAR_ABSTRACTION = "Calls*";

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
