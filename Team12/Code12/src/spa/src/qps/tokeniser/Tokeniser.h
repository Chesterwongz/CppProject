#pragma once

#include "qps/token/QueryToken.h"
#include <string>
#include <vector>

class Tokeniser {
public:

	std::vector<QueryToken>* convertToTokens(std::string* query);

private:
	std::vector<QueryToken> processFragment(std::string queryFragment, std::vector<QueryToken>* tokens);

	std::vector<std::string> getDesignEntitySynonyms(std::vector<std::string> whitespaceDelimitedFragments, std::size_t* iPtr);

	std::string getRelationship(std::vector<std::string> whitespaceDelimitedFragments, std::size_t* iPtr);

	std::string getPatternSynonym(std::vector<std::string> whitespaceDelimitedFragments, std::size_t* iPtr);

	std::vector<std::string> getArguments(std::vector<std::string> whitespaceDelimitedFragments, std::size_t* iPtr);

};


typedef std::vector<std::string> UnvalidatedTokens;
