#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "common/exceptions/Exception.h"
#include "Keywords.h"
#include "Tokeniser.h"
#include "TokeniserUtil.h"
#include "../token/QueryToken.h"

using std::string;
using std::vector;

std::vector<QueryToken>* Tokeniser::convertToTokens(std::string* query) {
    vector<QueryToken> tokens;
    vector<string> queryFragments;

    queryFragments = TokeniserUtil::delimitString(*query, semicolon); // delimit by semicolon

    for (string queryFragment : queryFragments) {
        processFragment(queryFragment, &tokens);
    }

    return &tokens;
}

// creates the respective tokens and adds it to tokens
vector<QueryToken> Tokeniser::processFragment(string queryFragment, vector<QueryToken>* tokens) {
    vector<string> whitespaceDelimitedFragments;
    vector<QueryToken> newTokens;
    std::size_t length;

    whitespaceDelimitedFragments = TokeniserUtil::delimitString(queryFragment, whitespace); // delimit by whitespace
    length = whitespaceDelimitedFragments.size();

    std::size_t i = 0;

    // apart from the else block that throws an error, every if block will at least increment i by 1
    // no risk of infinite loop
    // i didnt want to use for loop cos i will have to decrement i once im done with each block which can be quite messy
    while (i < length) {
        string currWord = whitespaceDelimitedFragments[i];
        if (TokeniserUtil::isDesignEntity(currWord)) {
            // getsynonym and create a DeclarationToken
            vector<string> designEntitySynonyms = getDesignEntitySynonyms(whitespaceDelimitedFragments, &i);
            newTokens = DeclartiveTokenFactory.createToken(currWord, designEntitySynonyms);
        }
        else if (TokeniserUtil::isSelect(currWord)) {
            // getSynonym and create SelectTokens
            vector<string> selectSynonyms = getArguments(whitespaceDelimitedFragments, &i);
            newTokens = SelectTokenFactory.createToken(currWord, selectSynonyms);
        }
        else if (TokeniserUtil::isSuchThat(whitespaceDelimitedFragments, &i)) {
            // get relationship, relationship args and create conditional tokens
            string relationship = getRelationship(whitespaceDelimitedFragments, &i);
            vector<string> relationshipArgs = getArguments(whitespaceDelimitedFragments, &i);
            newTokens = ConditionalTokenFactory.createToken(relationship, relationshipArgs);
        }
        else if (TokeniserUtil::isPattern(currWord)) {
            // get pattern, pattern args and create patternTokens
            string patternSynonym = getPatternSynonym(whitespaceDelimitedFragments, &i);
            vector<string> patternArgs = getArguments(whitespaceDelimitedFragments, &i);
            newTokens = PatternTokenFactory.createToken(patternSynonym, patternArgs);
        }
        else {
            // TODO: throw unexpected token error
            // currently using runtime error as a placeholder
            throw std::runtime_error("this is just a placeholder");
        }

        // add newTokens to tokens
        (*tokens).insert((*tokens).end(), newTokens.begin(), newTokens.end());
    }

}

// method to get synonym if whitespaceDelimitedFragments[entity] is a designEntity removes comma where applicable
// eg1. whitespaceDelimitedFragments = ["stmt", "v1,", "v2"], entityIndex = 0
// then synonyms = ["v1", "v2"], comma removed from "v1,"
// eg2. whitespaceDelimitedFragments = ["stmt", "v1,", "v2,"] entity index = 0
// then synonyms = ["v1", "v2,"], comma removed from "v1," only and not "v2," since "v2," is not proceeded by any tokens
// eg3. whitespaceDelimitedFragments = ["stmt", "v1", "v2,", v3] entity index = 0
// then synonyms = ["v1 v2", "v3"], v1 and v2 are concatenated since there is no comma separating them
vector<string> Tokeniser::getDesignEntitySynonyms(vector<string> whitespaceDelimitedFragments, std::size_t* iPtr) {

    if (!TokeniserUtil::isExistSubsequentTokens(whitespaceDelimitedFragments, *iPtr)) {
        // currently using runtime error as a placeholder
        throw std::runtime_error("this is just a placeholder");
    }

    (*iPtr)++;

    string synonym = "";
    vector<string> synonyms;
    
    for (std::size_t k = *iPtr; k < whitespaceDelimitedFragments.size(); k++) {
        if (synonym.empty()) {
            synonym += whitespaceDelimitedFragments[k];
        }
        else {
            synonym += whitespace;
            synonym += whitespaceDelimitedFragments[k];
        }

        if (TokeniserUtil::isEndsWithComma(synonym) && TokeniserUtil::isExistSubsequentTokens(whitespaceDelimitedFragments, k)) {
            // ends with comma and there are subsequent tokens
            synonym.pop_back(); // remove ending comma
            synonyms.push_back(synonym);
        }
        
        (*iPtr)++;
    }

    // add the final synonym if exists
    if (!synonym.empty()) {
        synonyms.push_back(synonym);
    }

    return synonyms;
}

// method to get arguments if whitespaceDelimitedFragments[*iPtr] == "select" / "such" (followed by "that") / "pattern"
// this method can be generalised for all 3 cases since in a select statement, each of these sections will be terminated by "pattern" / "such that"
vector<string> Tokeniser::getArguments(vector<string> whitespaceDelimitedFragments, std::size_t* iPtr) {

    if (!TokeniserUtil::isExistSubsequentTokens(whitespaceDelimitedFragments, *iPtr)) {
        // currently using runtime error as a placeholder
        throw std::runtime_error("this is just a placeholder");
    }

    vector<string> arguments;

    std::size_t length = whitespaceDelimitedFragments.size();

    (*iPtr)++;

    for (int k = *iPtr; k < length; k++) {
        string currWord = whitespaceDelimitedFragments[k];
        if ((currWord != pattern && currWord != suchThat[0]) ||
            (currWord == suchThat[0] && isArgumentSuch(whitespaceDelimitedFragments, k))) {
            // currWord is an argument

            arguments.push_back(whitespaceDelimitedFragments[k]);
            (*iPtr)++;
        }
        else {
            // currword is either "pattern" or "such" followed by "that"
            // all the arguments for the earlier keyword have already been captured
            break;
        }

    }

    return arguments;
}

// method to get relationship (i.e. Follows/Modifies etc) if whitespaceDelimitedFragments[*iPtr] == "such" and 
// whitespaceDelimitedFragments[*iPtr + 1] == "that"
// this method DOES NOT do the checking of "such that", it is a prereq to call this method
string Tokeniser::getRelationship(vector<string> whitespaceDelimitedFragments, std::size_t* iPtr) {
    // whitespaceDelimitedFragments[*iPtr] = "such"
    // increment i to get "that"
    (*iPtr)++;

    // check if there are tokens after "such that"
    if (!TokeniserUtil::isExistSubsequentTokens(whitespaceDelimitedFragments, *iPtr)) {
        // currently using runtime error as a placeholder
        throw std::runtime_error("this is just a placeholder");
    }

    (*iPtr)++;
    string relationship = whitespaceDelimitedFragments[*iPtr];

    return relationship;
}

// very similar to getRelationShip()
// only diff is that getRelationship() increments the iPtr an additional time since "such that" is 2 words compared to "pattern" which is only 1
// pretty sure this violates DRY
// not sure if i combine the 2 methods and use a boolean flag to determine whether to incr iPtr an additional time would be too confusing.
// need opinions
string Tokeniser::getPatternSynonym(vector<string> whitespaceDelimitedFragments, std::size_t* iPtr) {

    // check if there are tokens after "pattern"

    if (!TokeniserUtil::isExistSubsequentTokens(whitespaceDelimitedFragments, *iPtr)) {
        // currently using runtime error as a placeholder
        throw std::runtime_error("this is just a placeholder");
    }

    (*iPtr)++;
    string relationship = whitespaceDelimitedFragments[*iPtr];

    return relationship;
}
