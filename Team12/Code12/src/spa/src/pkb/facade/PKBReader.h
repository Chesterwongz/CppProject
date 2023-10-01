#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>

#include "pkb/facade/PKBStorage.h"

#include "pkb/interfaces/readers/IDesignEntitiesReader.h"
#include "pkb/interfaces/readers/IFollowsReader.h"
#include "pkb/interfaces/readers/IParentReader.h"
#include "pkb/interfaces/readers/IPatternReader.h"
#include "pkb/interfaces/readers/IUsesReader.h"
#include "pkb/interfaces/readers/IModifiesReader.h"
#include "pkb/interfaces/readers/IStatementReader.h"

class PKBReader : public virtual IDesignEntitiesReader, public virtual IFollowsReader,
    public virtual IParentReader, public virtual IPatternReader, 
    public virtual IUsesReader, public virtual IModifiesReader, public virtual IStatementReader {

public:
    explicit PKBReader(PKBStorage& storage) : storage(storage) {};
    virtual ~PKBReader() = default;

    // return the names of all variables in the program
    virtual std::set<std::string> getAllVariables();

    // return the values of all constants in the program
    virtual std::set<std::string> getAllConstants();

    // return the names of all procedures in the program
    virtual std::set<std::string> getAllProcedures();

    // return the statement numbers of specified statement type
    virtual std::set<std::string> getStatement(StmtType statementType);

    // return the statement number of the statement immediately following statementNumber
    // return s2 that satisfies Follows(s1, s2) and is of same type as statementType
    virtual std::string getFollowing(int statementNumber, StmtType statementType);

    // return the statement number of the statement that statementNumber immediately follows
    // return s1 that satisfies Follows(s1, s2) and is of same type as statementType
    virtual std::string getFollowed(int statementNumber, StmtType statementType);

    // return true if Follows(statementNumber, followingStatement) holds and false otherwise
    virtual bool isFollows(int statementNumber, int followingStatement);

    // return all pairs (s1,s2) that satisfy Follows(s1, s2) and satisfying statement type restriction
    virtual std::vector<std::pair<std::string, std::string>> getFollowsPairs(StmtType statementType1, StmtType statementType2);

    // return all pairs (s1, s2) that satisfy Follows*(s1, s2) where s2 is of same type as statementType and s1 is statementNumber 
    virtual std::vector<std::pair<std::string, std::string>> getFollowsStar(int statementNumber, StmtType statementType);

    // return all pairs (s1, s2) that satisfy Follows*(s1, s2) where s1 is of same type as statementType and s2 is statementNumber 
    virtual std::vector<std::pair<std::string, std::string>> getFollowedStar(int statementNumber, StmtType statementType);

    // return true if Follows*(statementNumber, followingStatement) holds and false otherwise
    virtual bool isFollowsStar(int statementNumber, int followingStatement);

    // return all pairs (s1,s2) that satisfy Follows*(s1, s2) and satisfying statement type restriction
    virtual std::vector<std::pair<std::string, std::string>> getFollowsStarPairs(StmtType statementType1, StmtType statementType2);

    // return all pairs (s1, s2) that satisfy Parent(s1, s2) where s2 is of same type as statementType and s1 is statementNumber
    virtual std::vector<std::pair<std::string, std::string>> getImmediateChildrenOf(int statementNumber, StmtType statementType);

    // return a pair (s1, s2) that satisfy Parent(s1, s2) where s1 is of same type as statementType and s2 is statementNumber
    virtual std::pair<std::string, std::string> getImmediateParentOf(int statementNumber, StmtType statementType);

    // return true if Parent(statementNumber, followingStatement) holds and false otherwise
    virtual bool isParent(int statementNumber, int childStatement);

    // return all pairs (s1,s2) that satisfy Parent(s1, s2) and satisfying statement type restriction
    virtual std::vector<std::pair<std::string, std::string>> getParentChildPairs(StmtType parentType, StmtType childType);

    // return all pairs (s1, s2) that satisfy Parent*(s1, s2) where s2 is of same type as statementType and s1 is statementNumber
    virtual std::vector<std::pair<std::string, std::string>> getChildrenStarOf(int statementNumber, StmtType statementType);

    // return all pairs (s1, s2) that satisfy Parent*(s1, s2) where s1 is of same type as statementType and s2 is statementNumber
    virtual std::vector<std::pair<std::string, std::string>> getParentStarOf(int statementNumber, StmtType statementType);

    // return true if Parent*(statementNumber, followingStatement) holds and false otherwise
    virtual bool isParentStar(int statementNumber, int childStatement);

    // return all pairs (s1,s2) that satisfy Parent*(s1, s2) and satisfying statement type restriction
    virtual std::vector<std::pair<std::string, std::string>> getParentChildStarPairs(StmtType parentType, StmtType childType);

    // return all s that satisfy Modifies(s, v) where v is variableName and s is of same type as statementType
    virtual std::vector<std::string> getStatementsModifying(const std::string& variableName, StmtType statementType);

    // return all pairs (s, v) that satisfy Modifies(s, v) where s is statementNumber and also the correct statementType mentioned
    virtual std::vector<std::pair<std::string, std::string>> getVariablesModifiedBy(int statementNumber, StmtType statementType);

    // check if Modifies(s, v) is true where s is statementNumber and v is the variable name
    virtual bool isVariableModifiedBy(const std::string& variableName, const std::string statementNumber);

    // return all s that satisfy Uses(s, v) where v is variableName and s is of same type as statementType
    virtual std::vector<std::string> getStatementsUsing(const std::string& variableName, StmtType statementType);

    // return all pairs (s, v) that satisfy Uses(s, v) where s is statementNumber and also the correct statementType mentioned
    virtual std::vector<std::pair<std::string, std::string>> getVariablesUsedBy(int statementNumber, StmtType statementType);

    // check if Used(s, v) is true where s is statementNumber and v is the variable name
    virtual bool isVariableUsedBy(const std::string& variableName, const std::string& statementNumber);

    // return all pairs (s, v) that satisfy Modifies (s, v) where s is of a particular type
    virtual std::vector<std::pair<std::string, std::string>> getAllModifiedVariables(StmtType statementType);

    // return all pairs (s, v) that satisfy Uses (s, v) where s is of a particular type
    virtual std::vector<std::pair<std::string, std::string>> getAllUsedVariables(StmtType statementType);

    // return list of statement numbers which match the given pattern exactly
    virtual std::vector<std::string> getExactAssignPattern(const std::string& variableName, const std::string& rpn, bool isSynonym);

    // return list of statement numbers which match the given pattern partially
    virtual std::vector<std::string> getPartialAssignPattern(const std::string& variableName, const std::string& rpn, bool isSynonym);

private:
    PKBStorage& storage;
};
