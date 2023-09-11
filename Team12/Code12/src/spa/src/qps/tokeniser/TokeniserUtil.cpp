#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "common/exceptions/Exception.h"
#include "qps/common/Keywords.h"
#include "TokeniserUtil.h"
#include "Tokeniser.h"
#include "../token/QueryToken.h"

using std::string;
using std::vector;

// returns true if word is a design entity
bool TokeniserUtil::isDesignEntity(string word) {

    auto it = designEntities.find(word);

    return it != designEntities.end();
}

// returns true if word is "select"
bool TokeniserUtil::isSelect(string word) {
    return word == select;
}

// returns true only if whitespaceDelimitedFragments[*iPtr] == "such" and whitespaceDelimitedFragments[*iPtr + 1] == "that"
bool TokeniserUtil::isSuchThat(vector<string> whitespaceDelimitedFragments, std::size_t* iPtr) {

    string currWord = whitespaceDelimitedFragments[*iPtr];


    if (currWord != suchThat[0]) {
        return false;
    }

    checkIfSubsequentTokensExist(whitespaceDelimitedFragments, *iPtr);

    string nextWord = whitespaceDelimitedFragments[*iPtr + 1];

    return nextWord == suchThat[1];
}

// returns true if word is "pattern"
bool TokeniserUtil::isPattern(string word) {
    return word == pattern;
}

// checks if "such" is an argument or part of the keyphrase "such that"
// returns true if such is an argument. 
// i.e. "Select such such that..." => first :such" returns true
bool TokeniserUtil::isArgumentSuch(vector<string> whitespaceDelimitedFragments, std::size_t suchIndex) {
    std::size_t length = whitespaceDelimitedFragments.size();

    return suchIndex < length - 1 && whitespaceDelimitedFragments[suchIndex + 1] != suchThat[1];
}

// returns a vector of strings delimited by "delimiter"
// does not include empty strings in the result
// i.e. "hello i am       sad" delimited by ' ' => ["hello", "i", "am", "sad"]
vector<string> TokeniserUtil::delimitString(string str, char delimiter) {
    vector<string> delimitedFragments;
    stringstream ss(str);
    string fragment;
    while (std::getline(ss, fragment, delimiter)) {
        if (fragment != "") {
            delimitedFragments.push_back(fragment);
        }
    }

    return delimitedFragments;
}

//method to check if currIndex is the last index of stringVec
// returns true if currIndex is NOT the last index of stringVec;
bool TokeniserUtil::isExistSubsequentTokens(vector<string> stringVec, std::size_t currIndex) {
    std::size_t length = stringVec.size();

    if (currIndex >= length - 1) {
        // means it is at least the last element in the vector
        // so no subsequent tokens exist
        return false;
    }

    return true;
}

// returns true if the last character of str is ',' and false otherwise
bool TokeniserUtil::isEndsWithComma(string str) {
    if (!str.empty() && str.back() == comma) {
        return true;
    }
    return false;
}
