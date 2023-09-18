#pragma once

#include <regex>
#include <string>

using std::regex, std::string, std::regex_match;

class PQLParserUtils {
public:
	explicit PQLParserUtils() = default;
	static bool isValidName(string data);
	static bool isValidInteger(string data);
	static bool isSynonym(string data);
	static bool isStmtRef(string data);
	static bool isEntRef(string data);
};
