#pragma once

#include "pkb/facade/PKBReader.h"
#include "qps/argument/IArgument.h"
#include "qps/argument/argumentFactory/ArgumentFactory.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

class MockPKBReader : public PKBReader {
public:
    explicit MockPKBReader(struct PKBStorage& storage) : PKBReader(storage) {};

    static unique_ptr<MockPKBReader> buildMockPKBReader();

    // return the names of all variables in the program
    set<string> getAllVariables() override;

    // return the statement numbers of specified statement type
    set<string> getStatement(StmtType statementType) override;

    // return all pairs (s1,s2) that satisfy Follows(s1, s2) and satisfying statement type restriction
    vector<pair<string, string>> getFollowsPairs(StmtType statementType1, StmtType statementType2) override;

    // return all pairs (s1,s2) that satisfy Follows*(s1, s2) and satisfying statement type restriction
    vector<pair<string, string>> getFollowsStarPairs(StmtType statementType1, StmtType statementType2) override;

    // return all pairs (s1,s2) that satisfy Parent(s1, s2) and satisfying statement type restriction
    vector<pair<string, string>> getParentChildPairs(StmtType parentType, StmtType childType) override;

    // return all pairs (s1,s2) that satisfy Parent*(s1, s2) and satisfying statement type restriction
    vector<pair<string, string>> getParentChildStarPairs(StmtType parentType, StmtType childType) override;

    // return all s that satisfy Modifies(s, v) where v is variableName and s is of same type as statementType
    vector<string> getStatementsModifying(string variableName, StmtType statementType) override;

    // return all s that satisfy Uses(s, v) where v is variableName and s is of same type as statementType
    vector<string> getStatementsUsing(string variableName, StmtType statementType) override;

    // return all pairs (s, v) that satisfy Modifies (s, v) where s is of a particular type
    vector<pair<string, string>> getAllModifiedVariables(StmtType statementType) override;

    // return all pairs (s, v) that satisfy Uses (s, v) where s is of a particular type
    vector<pair<string, string>> getAllUsedVariables(StmtType statementType) override;
};
