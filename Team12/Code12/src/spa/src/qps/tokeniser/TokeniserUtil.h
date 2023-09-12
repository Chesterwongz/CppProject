#pragma once

#include "qps/token/QueryToken.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

const char semicolon = ';';
const char whitespace = ' ';
const char comma = ',';
const char newline = '\n';

class TokeniserUtil {
public:
	static bool isDesignEntity(string word);

	static bool isSelect(string word);

	static bool isSuchThat(vector<string> whitespaceDelimitedFragments, std::size_t* iPtr);

	static bool isPattern(string word);

	static bool isArgumentSuch(vector<string> whitespaceDelimitedFragments, std::size_t suchIndex);

	static vector<string> delimitString(string str, char delimiter);

	static bool isExistSubsequentTokens(vector<string> stringVec, std::size_t currIndex);

	static bool isEndsWithComma(string str);
};
