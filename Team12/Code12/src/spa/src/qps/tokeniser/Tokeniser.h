#pragma once

#include "qps/token/QueryToken.h"
#include <string>
#include <vector>

using std::string, std::vector, std::size_t;

class Tokeniser {
public:

	vector<QueryToken>* convertToTokens(string* query);

private:
	vector<QueryToken> processFragment(string queryFragment, vector<QueryToken>* tokens);

	vector<string> getDesignEntitySynonyms(vector<string> whitespaceDelimitedFragments, size_t* iPtr);

	string getRelationship(vector<string> whitespaceDelimitedFragments, size_t* iPtr);

	string getPatternSynonym(vector<string> whitespaceDelimitedFragments, size_t* iPtr);

	vector<string> getArguments(vector<string> whitespaceDelimitedFragments, size_t* iPtr);

};


typedef vector<string> UnvalidatedTokens;
