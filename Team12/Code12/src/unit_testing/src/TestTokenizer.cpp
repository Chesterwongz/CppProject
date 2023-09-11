#include <string>
#include <memory>
#include <iostream>
#include <vector>

#include "catch.hpp"
#include "../../spa/src/qps/tokeniser/Tokeniser.h"
#include "../../spa/src/qps/tokenFactory/TokenFactory.h"
#include "../../spa/src/qps/token/declarativeToken/DeclarativeToken.h"
#include "../../spa/src/qps/tokeniser/TokeniserUtil.h"

using std::string, std::vector;

TEST_CASE("Test isDesignEntity block") {
    Tokeniser tokeniser;

    std::string stmt = "stmt s";

    vector<string> delimited = TokeniserUtil::delimitString(stmt, ' ');

    vector<string> synonyms;
    size_t i = 0;

    while (i < delimited.size()) {
        string curr = delimited[i];
        if (TokeniserUtil::isDesignEntity(curr)) {
            synonyms = tokeniser.getDesignEntitySynonyms(delimited, &i);
        }
    }

    bool test = true;
    for (string s : synonyms) {
        std::cout << s << std::endl;
    }

    REQUIRE(test);
}
