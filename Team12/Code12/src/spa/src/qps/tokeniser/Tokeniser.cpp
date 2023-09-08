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

const char semicolon = ';';
const char whitespace = ' ';

std::vector<QueryToken>* Tokeniser::convertToTokens(std::string* query) {
    std::vector<QueryToken> tokens;
    std::vector<std::string> queryFragments;

    queryFragments = TokeniserUtil::delimitString(*query, semicolon); // delimit by semicolon

    for (std::string queryFragment : queryFragments) {
        processFragment(queryFragment, &tokens);
    }

    return &tokens;
}

// creates the respective tokens and adds it to tokens
std::vector<QueryToken> Tokeniser::processFragment(std::string queryFragment, std::vector<QueryToken>* tokens) {
    std::vector<std::string> whitespaceDelimitedFragments;
    std::vector<QueryToken> newTokens;
    std::size_t length;

    whitespaceDelimitedFragments = TokeniserUtil::delimitString(queryFragment, whitespace); // delimit by whitespace
    length = whitespaceDelimitedFragments.size();

    std::size_t i = 0;

    // apart from the else block that throws an error, every if block will at least increment i by 1
    // no risk of infinite loop
    // i didnt want to use for loop cos i will have to decrement i once im done with each block which can be quite messy
    while (i < length) {
        std::string currWord = whitespaceDelimitedFragments[i];
        if (TokeniserUtil::isDesignEntity(currWord)) {
            // getsynonym and create a DeclarationToken
            std::vector<std::string> designEntitySynonyms = getDesignEntitySynonyms(whitespaceDelimitedFragments, &i);
            newTokens = DeclartiveTokenFactory.createToken(currWord, designEntitySynonyms);
        }
        else if (TokeniserUtil::isSelect(currWord)) {
            // getSynonym and create SelectTokens
            std::vector<std::string> selectSynonyms = getArguments(whitespaceDelimitedFragments, &i);
            newTokens = SelectTokenFactory.createToken(currWord, selectSynonyms);
        }
        else if (TokeniserUtil::isSuchThat(whitespaceDelimitedFragments, &i)) {
            // get relationship, relationship args and create conditional tokens
            std::string relationship = getRelationship(whitespaceDelimitedFragments, &i);
            std::vector<std::string> relationshipArgs = getArguments(whitespaceDelimitedFragments, &i);
            newTokens = ConditionalTokenFactory.createToken(relationship, relationshipArgs);
        }
        else if (TokeniserUtil::isPattern(currWord)) {
            // get pattern, pattern args and create patternTokens
            std::string patternSynonym = getPatternSynonym(whitespaceDelimitedFragments, &i);
            std::vector<std::string> patternArgs = getArguments(whitespaceDelimitedFragments, &i);
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

// method to get synonym if whitespaceDelimitedFragments[entity] is a designEntity
// eg. whitespaceDelimitedFragments = ["stmt", "v1,", "v2"], entityIndex = 1
// then synonyms = ["v1,", "v2"]
std::vector<std::string> Tokeniser::getDesignEntitySynonyms(std::vector<std::string> whitespaceDelimitedFragments, std::size_t* iPtr) {

    TokeniserUtil::checkIfSubsequentTokensExist(whitespaceDelimitedFragments, *iPtr);

    (*iPtr)++;

    std::vector <std::string> synonyms;

    for (int k = *iPtr; k < whitespaceDelimitedFragments.size(); k++) {
        synonyms.push_back(whitespaceDelimitedFragments[k]);
        (*iPtr)++;
    }

    return synonyms;
}

// method to get arguments if whitespaceDelimitedFragments[*iPtr] == "select" / "such" (followed by "that") / "pattern"
// this method can be generalised for all 3 cases since in a select statement, each of these sections will be terminated by "pattern" / "such that"
std::vector<std::string> Tokeniser::getArguments(std::vector<std::string> whitespaceDelimitedFragments, std::size_t* iPtr) {

    TokeniserUtil::checkIfSubsequentTokensExist(whitespaceDelimitedFragments, *iPtr);

    std::vector<std::string> arguments;

    std::size_t length = whitespaceDelimitedFragments.size();

    (*iPtr)++;

    for (int k = *iPtr; k < length; k++) {
        std::string currWord = whitespaceDelimitedFragments[k];
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
std::string Tokeniser::getRelationship(std::vector<std::string> whitespaceDelimitedFragments, std::size_t* iPtr) {
    // whitespaceDelimitedFragments[*iPtr] = "such"
    // increment i to get "that"
    (*iPtr)++;

    TokeniserUtil::checkIfSubsequentTokensExist(whitespaceDelimitedFragments, *iPtr); // check if there are tokens after "such that"

    (*iPtr)++;
    std::string relationship = whitespaceDelimitedFragments[*iPtr];

    return relationship;
}

// very similar to getRelationShip()
// only diff is that getRelationship() increments the iPtr an additional time since "such that" is 2 words compared to "pattern" which is only 1
// pretty sure this violates DRY
// not sure if i combine the 2 methods and use a boolean flag to determine whether to incr iPtr an additional time would be too confusing.
// need opinions
std::string Tokeniser::getPatternSynonym(std::vector<std::string> whitespaceDelimitedFragments, std::size_t* iPtr) {

    TokeniserUtil::checkIfSubsequentTokensExist(whitespaceDelimitedFragments, *iPtr); // check if there are tokens after "such that"

    (*iPtr)++;
    std::string relationship = whitespaceDelimitedFragments[*iPtr];

    return relationship;
}
