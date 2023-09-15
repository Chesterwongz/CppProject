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
    std::set<std::string> getStatement(StmtType statementType);

    // return the statement number of the statement immediately following statementNumber 
    // return s1 that satisfies Follows(s1, s2) and is of same type as statementType
    std::string getFollowing(int statementNumber, StmtType statementType);

    // return the statement number of the statement that statementNumber immediately follows
    // return s2 that satisfies Follows(s1, s2) and is of same type as statementType
    std::string getFollowed(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Follows(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<std::string, std::string>> getFollowsPairs(StmtType statementType1, StmtType statementType2);

    // return all s2 that satisfy Follows*(s1, s2) and is of same type as statementType where s1 is statementNumber 
    std::vector<std::pair<std::string, std::string>> getFollowsStar(int statementNumber, StmtType statementType);

    // return all s1 that satisfy Follows*(s1, s2) and is of same type as statementType where s2 is statementNumber 
    std::vector<std::pair<std::string, std::string>> getFollowedStar(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Follows*(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<std::string, std::string>> getFollowsStarPairs(StmtType statementType1, StmtType statementType2);

    // return all s2 that satisfy Parent(s1, s2) and is of same type as statementType where s1 is statementNumber
    std::vector<std::pair<std::string, std::string>> getImmediateChildrenOf(int statementNumber, StmtType statementType);

    // return all s1 that satisfy Parent(s1, s2) and is of same type as statementType where s2 is statementNumber
    std::vector<std::pair<std::string, std::string>> getImmediateParentOf(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Parent(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<std::string, std::string>> getParentChildPairs(StmtType parentType, StmtType childType);

    // return all s2 that satisfy Parent*(s1, s2) and is of same type as statementType where s1 is statementNumber
    std::vector<std::pair<std::string, std::string>>  getChildrenStarOf(int statementNumber, StmtType statementType);

    // return all s1 that satisfy Parent*(s1, s2) and is of same type as statementType where s2 is statementNumber
    std::vector<std::pair<std::string, std::string>>  getParentStarOf(int statementNumber, StmtType statementType);

    // return all pairs (s1,s2) that satisfy Parent*(s1, s2) and satisfying statement type restriction
    std::vector<std::pair<std::string, std::string>> getParentChildStarPairs(StmtType parentType, StmtType childType);

    // return all s that satisfy Modifies(v, s) where v is variableName and s is of same type as statementType
    std::vector<std::pair<std::string, std::string>> getStatementsModifying(const std::string& variableName, StmtType statementType);

    // return all v that satisfy Modifies(v, s) where s is statementNumber
    // will only return variables if s is also the correct statementType mentioned
    std::vector<std::pair<std::string, std::string>> getVariablesModifiedBy(int statementNumber, StmtType statementType);

    // return all s that satisfy Uses(v, s) where v is variableName and s is of same type as statementType
    std::vector<std::pair<std::string, std::string>> getStatementsUsing(const std::string& variableName, StmtType statementType);

    // return all v that satisfy Uses(v, s) where s is statementNumber
    // will only return variables if s is also the correct statementType mentioned
    std::vector<std::pair<std::string, std::string>> getVariablesUsedBy(int statementNumber, StmtType statementType);

    std::vector<std::pair<std::string, std::string>> getAllStatementsModifying(std::string variableName);

    std::vector<std::pair<std::string, std::string>> getAllStatementsUsing(std::string variableName);

    // return all variables that are used by statements of a particular type
    std::vector<std::pair<std::string, std::string>> getAllUsedVariables(StmtType statementType);

    // return all variables that are modified by statements of a particular type
    std::vector<std::pair<std::string, std::string>> getAllModifiedVariables(StmtType statementType);

    // return all statement numbers of a particular statement type that use a variable 
    std::vector<std::pair<std::string, std::string>> getAllUsingStatements(StmtType statementType);

    // return all statement numbers of a particular statement type that modify a variable 
    std::vector<std::pair<std::string, std::string>> getAllModifyingStatements(StmtType statementType);

private:
    struct Storage& storage;
};

