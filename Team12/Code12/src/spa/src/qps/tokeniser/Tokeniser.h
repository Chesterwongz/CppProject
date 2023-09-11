#pragma once

#include <string>
#include <vector>
#include <memory>

#include "qps/token/QueryToken.h"
#include "qps/tokenFactory/TokenFactory.h"

using std::string, std::vector, std::size_t, std::unique_ptr;

typedef vector<unique_ptr<QueryToken>> TokenStream;
typedef vector<string> UnvalidatedTokens;

class Tokeniser {
public:
	TokenStream convertToTokens(string query);

//private:
	void processFragment(string queryFragment, TokenStream& tokens);

	vector<string> getDesignEntitySynonyms(vector<string> whitespaceDelimitedFragments, size_t* iPtr);

	string getRelationship(vector<string> whitespaceDelimitedFragments, size_t* iPtr);

	string getPatternSynonym(vector<string> whitespaceDelimitedFragments, size_t* iPtr);

	vector<string> getArguments(vector<string> whitespaceDelimitedFragments, size_t* iPtr);

};

