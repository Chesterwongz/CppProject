#pragma once

#include <string>
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <unordered_set>

#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"

class PKBReader {
public:
    // Constructor
    PKBReader() = default;;

    // get the names of all variables in the program
    std::unordered_set<std::string> getAllVariables();

    // get the values of all constants in the program
    std::unordered_set<std::string> getAllConstants();

    // get the names of all procedures in the program
    std::unordered_set<std::string> getAllProcedures();

    // return the statement numbers of statements
    std::unordered_set<int> getStatement(StmtType statementType);

    int getFollowing(int statementNumber, StmtType statementType);

    int getFollowed(int statementNumber, StmtType statementType);

    std::unordered_set<int> getStatementsModifying(const std::string& variableName, StmtType statementType);

    std::unordered_set<std::string> getVariablesModifiedBy(int statementNumber, StmtType statementType);

    std::unordered_set<int> getStatementsUsing(const std::string& variableName, StmtType statementType);

    std::unordered_set<std::string> getVariablesUsedBy(int statementNumber, StmtType statementType);

    std::unordered_set<int> getAllStatementsModifying(std::string variableName);

    std::unordered_set<int> getAllStatementsUsing(std::string variableName);

    std::unordered_set<std::string> getAllUsedVariables();

    std::unordered_set<std::string> getAllModifiedVariables();

    std::unordered_set<int> getAllUsingStatements();

    std::unordered_set<int> getAllModifyingStatements();

    std::vector<std::pair<int, int>> getFollowsPairs(StmtType statementType1, StmtType statementType2);

    std::unordered_set<std::pair<int, int>> getFollowsPairs(std::string statementType1, std::string statementType2);

private:
    DesignEntitiesStorage designEntitiesStorage;
    FollowsStorage followsStorage;
    ModifiesStorage modifiesStorage;
    ParentStorage parentStorage;
    StatementStorage statementStorage;
    UsesStorage usesStorage;
};

