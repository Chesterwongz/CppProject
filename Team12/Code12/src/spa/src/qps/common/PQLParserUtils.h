#pragma once

#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "qps/parser/tokenizer/PQLTokenType.h"
#include "qps/parser/tokenizer/token/PQLToken.h"

using std::regex, std::string, std::regex_match, std::unordered_map,
    std::unordered_set;

typedef unordered_map<PQLTokenType, unordered_set<PQLTokenType>> PredictiveMap;

class PQLParserUtils {
 private:
  static unordered_map<string, PQLTokenType> keywordToTokenType;
  static unordered_map<char, PQLTokenType> delimiterToTokenType;
  static unordered_set<string> stmtEntities;
  static unordered_map<string, unordered_set<string>> entityToAttrRef;

 public:
  static unordered_map<AttrRef, ArgumentType> attrRefToType;
  PQLParserUtils() = default;
  static PQLTokenType isDelimiterToken(const char& c);
  static bool isDelimiter(const char& ch);
  static bool isStmtSynonym(const string& entity);
  static PQLTokenType getTokenTypeFromKeyword(const string& keyword);
  static bool isValidAttrRefFromSynonym(const string& synonymType,
                                        const string& ref);
};
