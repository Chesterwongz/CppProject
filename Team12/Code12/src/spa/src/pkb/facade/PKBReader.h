#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>

#include "pkb/facade/PKBStorage.h"
#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"

class PKBReader {
public:
    PKBReader(PKBStorage& storage) : storage(storage) {};

    // return the names of all variables in the program
    std::set<std::string> getAllVariables();

    // return the values of all constants in the program
    std::set<std::string> getAllConstants();

    // return the names of all procedures in the program
    std::set<std::string> getAllProcedures();

    // return the statement numbers of specified statement type
    std::set<std::string> getStatement(StmtType statementType);

    // return the statement number of the statement immediately following statementNumber 
    // return s2 that satisfies Follows(s1, s2) and is of same type as statementType
    std::string getFollowing(int statementNumber, StmtType statementType);

    // return the statement number of the statement that statementNumber immediately follows
    // return s1 that satisfies Follows(s1, s2) and is of same type as statementType
    std::string getFollowed(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Follows(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<std::string, std::string>> getFollowsPairs(StmtType statementType1, StmtType statementType2);

    // return all pairs (s1, s2) that satisfy Follows*(s1, s2) where s2 is of same type as statementType and s1 is statementNumber 
    std::vector<std::pair<std::string, std::string>> getFollowsStar(int statementNumber, StmtType statementType);

    // return all pairs (s1, s2) that satisfy Follows*(s1, s2) where s1 is of same type as statementType and s2 is statementNumber 
    std::vector<std::pair<std::string, std::string>> getFollowedStar(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Follows*(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<std::string, std::string>> getFollowsStarPairs(StmtType statementType1, StmtType statementType2);

    // return all pairs (s1, s2) that satisfy Parent(s1, s2) where s2 is of same type as statementType and s1 is statementNumber
    std::vector<std::pair<std::string, std::string>> getImmediateChildrenOf(int statementNumber, StmtType statementType);

    // return a pair (s1, s2) that satisfy Parent(s1, s2) where s1 is of same type as statementType and s2 is statementNumber
    std::pair<std::string, std::string> getImmediateParentOf(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Parent(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<std::string, std::string>> getParentChildPairs(StmtType parentType, StmtType childType);

    // return all pairs (s1, s2) that satisfy Parent*(s1, s2) where s2 is of same type as statementType and s1 is statementNumber
    std::vector<std::pair<std::string, std::string>> getChildrenStarOf(int statementNumber, StmtType statementType);

    // return all pairs (s1, s2) that satisfy Parent*(s1, s2) where s1 is of same type as statementType and s2 is statementNumber
    std::vector<std::pair<std::string, std::string>> getParentStarOf(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Parent*(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<std::string, std::string>> getParentChildStarPairs(StmtType parentType, StmtType childType);

    // return all s that satisfy Modifies(s, v) where v is variableName and s is of same type as statementType
    std::vector<std::string> getStatementsModifying(std::string variableName, StmtType statementType);

    // return all pairs (s, v) that satisfy Modifies(s, v) where s is statementNumber and also the correct statementType mentioned
    std::vector<std::pair<std::string, std::string>> getVariablesModifiedBy(int statementNumber, StmtType statementType);

    // return all s that satisfy Uses(s, v) where v is variableName and s is of same type as statementType
    std::vector<std::string> getStatementsUsing(std::string variableName, StmtType statementType);

    // return all pairs (s, v) that satisfy Uses(s, v) where s is statementNumber and also the correct statementType mentioned
    std::vector<std::pair<std::string, std::string>> getVariablesUsedBy(int statementNumber, StmtType statementType);

    // return all pairs (s, v) that satisfy Modifies (s, v) where s is of a particular type
    std::vector<std::pair<std::string, std::string>> getAllModifiedVariables(StmtType statementType);

    // return all pairs (s, v) that satisfy Uses (s, v) where s is of a particular type
    std::vector<std::pair<std::string, std::string>> getAllUsedVariables(StmtType statementType);

    // return list of statement numbers which match the given pattern exactly
    std::vector<std::string> getExactPattern(std::string variableName, std::string rpn);

    // return list of statement numbers which match the given pattern partially
    std::vector<std::string> getPartialPattern(std::string variableName, std::string rpn);

private:
    PKBStorage storage;
};

