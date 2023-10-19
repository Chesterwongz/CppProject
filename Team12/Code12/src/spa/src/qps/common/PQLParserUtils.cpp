#include "PQLParserUtils.h"

#include "qps/exceptions/QPSSyntaxError.h"
#include "qps/exceptions/QPSSemanticError.h"

unordered_map<string, PQLTokenType> PQLParserUtils::keywordToTokenType = {
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

    {ATTR_REF_PROC_NAME, PQL_ATTR_REF_TOKEN},
    {ATTR_REF_VAR_NAME, PQL_ATTR_REF_TOKEN},
    {ATTR_REF_VALUE, PQL_ATTR_REF_TOKEN},
    {ATTR_REF_STMT_NUMBER, PQL_ATTR_REF_TOKEN},

    {PATTERN_KEYWORD, PQL_PATTERN_TOKEN},

    {WITH_KEYWORD, PQL_WITH_TOKEN},

    {NOT_KEYWORD, PQL_NOT_TOKEN}};

unordered_map<char, PQLTokenType> PQLParserUtils::delimiterToTokenType = {
    {pqlDelim::kSemicolonChar, PQL_SEMICOLON_TOKEN},
    {pqlDelim::kCommaChar, PQL_COMMA_TOKEN},
    {pqlDelim::kWildcardChar, PQL_WILDCARD_TOKEN},
    {pqlDelim::kOpenBracketChar, PQL_OPEN_BRACKET_TOKEN},
    {pqlDelim::kCloseBracketChar, PQL_CLOSE_BRACKET_TOKEN},
    {pqlDelim::kLeftAngleChar, PQL_LEFT_ANGLE_TOKEN},
    {pqlDelim::kRightAngleChar, PQL_RIGHT_ANGLE_TOKEN},
    {pqlDelim::kPeriodChar, PQL_PERIOD_TOKEN},
    {pqlDelim::kEqualChar, PQL_EQUALS_TOKEN}};

unordered_set<string> PQLParserUtils::stmtEntities = {
    STMT_ENTITY, READ_ENTITY,  PRINT_ENTITY, ASSIGN_ENTITY,
    CALL_ENTITY, WHILE_ENTITY, IF_ENTITY};

unordered_map<string, unordered_set<string>> PQLParserUtils::entityToAttrRef = {
    {ASSIGN_ENTITY, {ATTR_REF_STMT_NUMBER}},
    {CALL_ENTITY, {ATTR_REF_PROC_NAME, ATTR_REF_STMT_NUMBER}},
    {CONSTANT_ENTITY, {ATTR_REF_VALUE}},
    {IF_ENTITY, {ATTR_REF_STMT_NUMBER}},
    {PRINT_ENTITY, {ATTR_REF_VAR_NAME, ATTR_REF_STMT_NUMBER}},
    {PROCEDURE_ENTITY, {ATTR_REF_PROC_NAME}},
    {READ_ENTITY, {ATTR_REF_VAR_NAME, ATTR_REF_STMT_NUMBER}},
    {STMT_ENTITY, {ATTR_REF_STMT_NUMBER}},
    {VARIABLE_ENTITY, {ATTR_REF_VAR_NAME}},
    {WHILE_ENTITY, {ATTR_REF_STMT_NUMBER}}};

unordered_map<AttrRef, ArgumentType> PQLParserUtils::attrRefToType = {
    {ATTR_REF_STMT_NUMBER, ArgumentType::INTEGER_TYPE},
    {ATTR_REF_VAR_NAME, ArgumentType::NAME_TYPE},
    {ATTR_REF_PROC_NAME, ArgumentType::NAME_TYPE},
    {ATTR_REF_VALUE, ArgumentType::INTEGER_TYPE},
};

PQLTokenType PQLParserUtils::isDelimiterToken(const char &c) {
  return delimiterToTokenType.find(c)->second;
}

bool PQLParserUtils::isDelimiter(const char &ch) {
  return delimiterToTokenType.find(ch) != delimiterToTokenType.end();
}

bool PQLParserUtils::isStmtSynonym(const std::string &entity) {
  return stmtEntities.find(entity) != stmtEntities.end();
}

PQLTokenType PQLParserUtils::getTokenTypeFromKeyword(const string &data) {
  auto entity = keywordToTokenType.find(data);

  if (entity != keywordToTokenType.end()) {
    return entity->second;
  } else {
    return PQL_NULL_TOKEN;
  }
}

bool PQLParserUtils::isValidAttrRefFromSynonym(const std::string &synonymType,
                                               const std::string &ref) {
  auto synRefPair = entityToAttrRef.find(synonymType);

  if (attrRefToType.find(ref) == attrRefToType.end()) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_ATTR_REF + ref);
  }

  if (synRefPair == entityToAttrRef.end()) return false;

  auto availRef = synRefPair->second;
  return availRef.find(ref) != availRef.end();
}
