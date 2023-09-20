#include "catch.hpp"

#include "qps/tokenizer/PQLTokenizer.h"
#include "qps/tokenizer/PQLTokenType.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

bool isEqual(vector<PQLTokenType> expected, PQLTokenStream& tokenStream) {

    for (PQLTokenType type : expected) {
        try {
            PQLToken &token = tokenStream.getCurrentToken();
            if (token.getType() != type) {
                return false;
            }
        } catch (QPSInvalidQueryException e) {
            return false;
        }
    }

    return true;
}

TEST_CASE("Simple Declaration") {
    string query = "stmt s1, s2;";
    vector<PQLTokenType> expected = {PQL_NAME_TOKEN, PQL_NAME_TOKEN, PQL_COMMA_TOKEN, PQL_NAME_TOKEN, PQL_SEMICOLON_TOKEN};
    PQLTokenizer tokenizer(query);
    unique_ptr<PQLTokenStream> res = tokenizer.tokenize();
    REQUIRE(isEqual(expected, *res));
}
