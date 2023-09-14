#pragma once

#include <string>
#include <iostream>
#include <set>
#include <map>
#include <string>
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
    // Constructor
    PKBReader(struct Storage& storage) : storage(storage) {};

    // return the names of all variables in the program
    std::set<std::string> getAllVariables();

    // return the values of all constants in the program
    std::set<std::string> getAllConstants();

    // return the names of all procedures in the program
    std::set<std::string> getAllProcedures();

    // return the statement numbers of specified statement type
    std::set<int> getStatement(StmtType statementType);

    // return the statement number of the statement immediately following statementNumber 
    // return s1 that satisfies Follows(s1, s2) and is of same type as statementType
    int getFollowing(int statementNumber, StmtType statementType);

    // return the statement number of the statement that statementNumber immediately follows
    // return s2 that satisfies Follows(s1, s2) and is of same type as statementType
    int getFollowed(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Follows(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<int, int>> getFollowsPairs(StmtType statementType1, StmtType statementType2);

    // return all s2 that satisfy Follows*(s1, s2) and is of same type as statementType where s1 is statementNumber 
    std::set<int> getFollowsStar(int statementNumber, StmtType statementType);

    // return all s1 that satisfy Follows*(s1, s2) and is of same type as statementType where s2 is statementNumber 
    std::set<int> getFollowedStar(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Follows*(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<int, int>> getFollowsStarPairs(StmtType statementType1, StmtType statementType2);

    // return all s2 that satisfy Parent(s1, s2) and is of same type as statementType where s1 is statementNumber
    std::set<int> getImmediateChildrenOf(int statementNumber, StmtType statementType);

    // return all s1 that satisfy Parent(s1, s2) and is of same type as statementType where s2 is statementNumber
    int getImmediateParentOf(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Parent(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<int, int>> getParentChildPairs(StmtType parentType, StmtType childType);

    // return all s2 that satisfy Parent*(s1, s2) and is of same type as statementType where s1 is statementNumber
    std::set<int> getChildrenStarOf(int statementNumber, StmtType statementType);

    // return all s1 that satisfy Parent*(s1, s2) and is of same type as statementType where s2 is statementNumber
    std::set<int> getParentStarOf(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Parent*(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<int, int>> getParentChildStarPairs(StmtType parentType, StmtType childType);

    // return all s that satisfy Modifies(v, s) where v is variableName and s is of same type as statementType
    std::set<int> getStatementsModifying(const std::string& variableName, StmtType statementType);

    // return all v that satisfy Modifies(v, s) where s is statementNumber
    // will only return variables if s is also the correct statementType mentioned
    std::set<std::string> getVariablesModifiedBy(int statementNumber, StmtType statementType);

    // return all s that satisfy Uses(v, s) where v is variableName and s is of same type as statementType
    std::set<int> getStatementsUsing(const std::string& variableName, StmtType statementType);

    // return all v that satisfy Uses(v, s) where s is statementNumber
    // will only return variables if s is also the correct statementType mentioned
    std::set<std::string> getVariablesUsedBy(int statementNumber, StmtType statementType);

    std::set<int> getAllStatementsModifying(std::string variableName);

    std::set<int> getAllStatementsUsing(std::string variableName);

    // return all variables that are used in the program
    std::set<std::string> getAllUsedVariables();

    // return all variables that are modified in the program
    std::set<std::string> getAllModifiedVariables();

    // return all statement numbers that use a variable
    std::set<int> getAllUsingStatements(StmtType statementType);

    // return all statement numbers that modify a variable
    std::set<int> getAllModifyingStatements(StmtType statementType);

private:
    struct Storage& storage;
};

