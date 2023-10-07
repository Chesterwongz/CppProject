//  #include <catch.hpp>
//
// #include "qps/exceptions/QPSInvalidQueryException.h"
// #include "qps/tokenizer/PQLTokenType.h"
// #include "qps/tokenizer/PQLTokenizer.h"
//
// bool isEqual(vector<PQLTokenType> expected, PQLTokenList tokenList) {
//  for (int i = 0; i < expected.size(); i++) {
//    try {
//      PQLToken& token = tokenList[i];
//      if (token.getType() != expected[i]) {
//        return false;
//      }
//    } catch (QPSInvalidQueryException& e) {
//      return false;
//    }
//  }
//
//  return true;
//}
//
// TEST_CASE("Simple Declaration") {
//  string query = "stmt s1, s2;";
//  vector<PQLTokenType> expected = {PQL_NAME_TOKEN, PQL_NAME_TOKEN,
//                                   PQL_COMMA_TOKEN, PQL_NAME_TOKEN,
//                                   PQL_SEMICOLON_TOKEN};
//  PQLTokenizer tokenizer(query);
//  unique_ptr<PQLTokenList> res = tokenizer.tokenize();
//  REQUIRE(isEqual(expected, *(res.get())));
//}
//
// TEST_CASE("query with literals") {
//  string query = "stmt s1, s2; assign a;\n Select a pattern a (\"x\", _)";
//  vector<PQLTokenType> expected = {
//      PQL_NAME_TOKEN,         PQL_NAME_TOKEN,         PQL_COMMA_TOKEN,
//      PQL_NAME_TOKEN,         PQL_SEMICOLON_TOKEN,    PQL_NAME_TOKEN,
//      PQL_NAME_TOKEN,         PQL_SEMICOLON_TOKEN,    PQL_NAME_TOKEN,
//      PQL_NAME_TOKEN,         PQL_NAME_TOKEN,         PQL_NAME_TOKEN,
//      PQL_OPEN_BRACKET_TOKEN, PQL_LITERAL_REF_TOKEN,  PQL_COMMA_TOKEN,
//      PQL_WILDCARD_TOKEN,     PQL_CLOSE_BRACKET_TOKEN};
//  PQLTokenizer tokenizer(query);
//  unique_ptr<PQLTokenList> res = tokenizer.tokenize();
//  REQUIRE(isEqual(expected, *(res.get())));
//}
//
// TEST_CASE("Invalid query with unmatched quote") {
//  string query = "\"unmatched";
//  PQLTokenizer tokenizer(query);
//
//  REQUIRE_THROWS_WITH(tokenizer.tokenize(),
//                      QPS_INVALID_QUERY_ERR_UNMATCHED_QUOTE);
//}
//
// TEST_CASE("test all symbols") {
//  string query = "()*,;";
//  vector<PQLTokenType> expected = {PQL_OPEN_BRACKET_TOKEN,
//                                   PQL_CLOSE_BRACKET_TOKEN,
//                                   PQL_ASTERISKS_TOKEN, PQL_COMMA_TOKEN,
//                                   PQL_SEMICOLON_TOKEN};
//  PQLTokenizer tokenizer(query);
//  unique_ptr<PQLTokenList> res = tokenizer.tokenize();
//  REQUIRE(isEqual(expected, *(res.get())));
//}
//
// TEST_CASE("invalid name") {
//  string query = "stmt sa&;";
//  PQLTokenizer tokenizer(query);
//
//  REQUIRE_THROWS_WITH(tokenizer.tokenize(), QPS_INVALID_QUERY_INAVLID_NAME);
//}
//
// TEST_CASE("query with literals and many whitespaces") {
//  string query =
//      "stmt       s1 ,     s2; assign     a;\n Select a      pattern a (   "
//      "\"x\",   _ )    ";
//  vector<PQLTokenType> expected = {
//      PQL_NAME_TOKEN,         PQL_NAME_TOKEN,         PQL_COMMA_TOKEN,
//      PQL_NAME_TOKEN,         PQL_SEMICOLON_TOKEN,    PQL_NAME_TOKEN,
//      PQL_NAME_TOKEN,         PQL_SEMICOLON_TOKEN,    PQL_NAME_TOKEN,
//      PQL_NAME_TOKEN,         PQL_NAME_TOKEN,         PQL_NAME_TOKEN,
//      PQL_OPEN_BRACKET_TOKEN, PQL_LITERAL_REF_TOKEN,  PQL_COMMA_TOKEN,
//      PQL_WILDCARD_TOKEN,     PQL_CLOSE_BRACKET_TOKEN};
//  PQLTokenizer tokenizer(query);
//  unique_ptr<PQLTokenList> res = tokenizer.tokenize();
//  REQUIRE(isEqual(expected, *(res.get())));
//}
//
// TEST_CASE("Invalid integer") {
//  string integer = "4d500";
//  PQLTokenizer tokenizer(integer);
//
//  REQUIRE_THROWS_WITH(tokenizer.tokenize(),
//  QPS_INVALID_QUERY_INAVLID_INTEGER);
//}
