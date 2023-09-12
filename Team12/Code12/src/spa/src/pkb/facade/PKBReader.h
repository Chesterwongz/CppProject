#ifndef PKBREADER_H
#define PKBREADER_H

#include <string>
#include <iostream>
#include <set>
#include <map>

#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"

class PKBReader {
public:
    // Constructor
    PKBReader();

    // get the names of all variables in the program
    std::unordered_set<std::string> getAllVariables();

    // get the values of all constants in the program
    std::unordered_set<int> getAllConstants();

    // get the names of all procedures in the program
    std::unordered_set<std::string> getAllProcedures();

    // return the statement numbers of statements
    std::unordered_set<int> getStatement(std::string statementType);

    int getFollowing(int statementNumber, std::string statementType);

    int getFollowed(int statementNumber, std::string statementType);

    std::unordered_set<int> getStatementsModifying(std::string variableName, std::string statementType);

    std::unordered_set<std::string> getVariablesModifiedBy(int statementNumber, std::string statementType);

    std::unordered_set<int> getStatementsUsing(std::string variableName, std::string statementType);

    std::unordered_set<std::string> getVariablesUsedBy(int statementNumber, std::string statementType);

    std::unordered_set<int> PKBReader::getAllStatementsModifying(std::string variableName);

    std::unordered_set<int> PKBReader::getAllStatementsUsing(std::string variableName);

    std::set<std::string> PKBReader::getAllUsedVariables();

    std::unordered_set<std::string> PKBReader::getAllModifiedVariables();

    std::unordered_set<int> PKBReader::getAllUsingStatements();

    std::set<int> PKBReader::getAllModifyingStatements();

    std::set<std::pair<int, int>> getFollowsPairs(std::string statementType1, std::string statementType2);


private:
    DesignEntitiesStorage designEntitiesStorage;
    FollowsStorage followsStorage;
    ModifiesStorage modifiesStorage;
    ParentStorage parentStorage;
    StatementStorage statementStorage;
    UsesStorage usesStorage;
};

#endif // PKBREADER_H
