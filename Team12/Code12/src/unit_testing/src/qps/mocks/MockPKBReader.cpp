#include "MockPKBReader.h"
#include "MockPKBReaderData.h"

unique_ptr<MockPKBReader> MockPKBReader::buildMockPKBReader() {
    struct PKBStorage storage = {};
    return std::make_unique<MockPKBReader>(storage);
}

set<string> MockPKBReader::getAllVariables() {
    return MOCK_VARIABLES;
}

set<string> MockPKBReader::getStatement(
        StmtType statementType) {
    return MOCK_STATEMENTS_SET;
}

vector<pair<string, string>> MockPKBReader::getFollowsPairs(
        StmtType statementType1,
        StmtType statementType2) {
    return MOCK_FOLLOWS_PAIRS;
}

vector<pair<string, string>> MockPKBReader::getFollowsStarPairs(
        StmtType statementType1,
        StmtType statementType2) {
    return MOCK_FOLLOWS_STARS_PAIRS;
}

vector<pair<string, string>> MockPKBReader::getParentChildPairs(
        StmtType parentType,
        StmtType childType) {
    return MOCK_PARENT_CHILD_PAIRS;
}

vector<pair<string, string>> MockPKBReader::getParentChildStarPairs(
        StmtType parentType,
        StmtType childType) {
    return MOCK_PARENT_CHILD_STAR_PAIRS;
}

vector<string> MockPKBReader::getStatementsModifying(
        string variableName,
        StmtType statementType) {
    return MOCK_MODIFYING_STATEMENTS;
}

vector<string> MockPKBReader::getStatementsUsing(
        string variableName,
        StmtType statementType) {
    return MOCK_USING_STATEMENTS;
}

vector<pair<string, string>> MockPKBReader::getAllModifiedVariables(
        StmtType statementType) {
    return MOCK_MODIFIED_PAIRS;
}

inline vector<pair<string, string>> MockPKBReader::getAllUsedVariables(
        StmtType statementType) {
    return MOCK_USED_PAIRS;
}
