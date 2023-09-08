#pragma once

#include "qps/token/QueryToken.h"
#include <string>
#include <vector>

class TokeniserUtil {
public:
	static bool isDesignEntity(std::string word);

	static bool isSelect(std::string word);

	static bool isSuchThat(std::vector<std::string> whitespaceDelimitedFragments, std::size_t* iPtr);

	static bool isPattern(std::string word);

	static bool isArgumentSuch(std::vector<std::string> whitespaceDelimitedFragments, std::size_t suchIndex);

	static std::vector<std::string> delimitString(std::string str, char delimiter);

	static void checkIfSubsequentTokensExist(std::vector<std::string> stringVec, std::size_t currIndex);
};
