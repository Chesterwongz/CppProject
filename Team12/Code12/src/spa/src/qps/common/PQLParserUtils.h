#pragma once

#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "qps/tokenizer/PQLTokenType.h"
#include "qps/token/PQLToken.h"

using std::regex, std::string, std::regex_match, std::unordered_map, std::unordered_set;

typedef unordered_map<PQLTokenType, unordered_set<PQLTokenType>> PredictiveMap;

class PQLParserUtils {
public:
	explicit PQLParserUtils() = default;
	static bool isValidName(string& data);
	static bool isValidInteger(string& data);
	static bool isSynonym(string data);
	static bool isStmtRef(string data);
	static bool isEntRef(string data);
    static PQLTokenType getTokenTypeFromKeyword(const string &keyword);
    static void processNameTokenInRelationships(PQLToken &curr, bool isInBracket);
    static bool isDelimiter(PQLTokenType tokenType);
    static bool isExpectedToken(PredictiveMap& pm, PQLTokenType prev, PQLTokenType curr);
};
