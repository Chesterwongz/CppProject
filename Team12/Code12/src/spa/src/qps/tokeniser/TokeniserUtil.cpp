#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "common/exceptions/Exception.h"
#include "Keywords.h"
#include "TokeniserUtil.h"
#include "Tokeniser.h"
#include "../token/QueryToken.h"

// returns true if word is a design entity
bool TokeniserUtil::isDesignEntity(std::string word) {

    auto it = std::find(designEntities.begin(), designEntities.end(), word);

    return it != designEntities.end();
}

// returns true if word is "select"
bool TokeniserUtil::isSelect(std::string word) {
    return word == select;
}

// returns true only if whitespaceDelimitedFragments[*iPtr] == "such" and whitespaceDelimitedFragments[*iPtr + 1] == "that"
bool TokeniserUtil::isSuchThat(std::vector<std::string> whitespaceDelimitedFragments, std::size_t* iPtr) {

    std::string currWord = whitespaceDelimitedFragments[*iPtr];


    if (currWord != suchThat[0]) {
        return false;
    }

    checkIfSubsequentTokensExist(whitespaceDelimitedFragments, *iPtr);

    std::string nextWord = whitespaceDelimitedFragments[*iPtr + 1];

    return nextWord == suchThat[1];
}

// returns true if word is "pattern"
bool TokeniserUtil::isPattern(std::string word) {
    return word == pattern;
}

// checks if "such" is an argument or part of the keyphrase "such that"
// returns true if such is an argument. 
// i.e. "Select such such that..." => first :such" returns true
bool TokeniserUtil::isArgumentSuch(std::vector<std::string> whitespaceDelimitedFragments, std::size_t suchIndex) {
    std::size_t length = whitespaceDelimitedFragments.size();

    return suchIndex < length - 1 && whitespaceDelimitedFragments[suchIndex + 1] != suchThat[1];
}

// returns a vector of strings delimited by "delimiter"
// does not include empty strings in the result
// i.e. "hello i am       sad" delimited by ' ' => ["hello", "i", "am", "sad"]
std::vector<std::string> TokeniserUtil::delimitString(std::string str, char delimiter) {
    std::vector<std::string> delimitedFragments;
    std::istringstream ss(str);
    std::string fragment;
    while (std::getline(ss, fragment, delimiter)) {
        if (fragment != "") {
            delimitedFragments.push_back(fragment);
        }
    }

    return delimitedFragments;
}

//method to check if currIndex is the last index of stringVec
void TokeniserUtil::checkIfSubsequentTokensExist(std::vector<std::string> stringVec, std::size_t currIndex) {
    std::size_t length = stringVec.size();

    if (currIndex >= length - 1) {
        // means it is at least the last element in the vector
        // so no subsequent tokens exist
        throw std::runtime_error("this is just a placeholder");
    }
}
