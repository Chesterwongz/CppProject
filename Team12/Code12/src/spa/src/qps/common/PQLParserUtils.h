#pragma once

#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "qps/token/PQLToken.h"
#include "qps/tokenizer/PQLTokenType.h"

using std::regex, std::string, std::regex_match, std::unordered_map,
    std::unordered_set;

typedef unordered_map<PQLTokenType, unordered_set<PQLTokenType>> PredictiveMap;

class PQLParserUtils {
 public:
  PQLParserUtils() = default;
  static PQLTokenType getTokenTypeFromKeyword(const string& keyword);
  static bool isDelimiter(PQLTokenType tokenType);
  static bool isExpectedToken(PredictiveMap& pm, PQLTokenType prev,
                              PQLTokenType curr);
};
