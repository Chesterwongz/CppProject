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
    std::vector<std::string> getAllVariables();

    // get the values of all constants in the program
    std::vector<int> getAllConstants();

    // get the names of all procedures in the program
    std::vector<std::string> getAllProcedures();

    // return the statement numbers of all statements
    std::unordered_set<int> getAllStmts();

    // return the statement numbers of all READ statements
    std::unordered_set<int> getAllRead();

    // return the statement numbers of all PRINT statements
    std::unordered_set<int> getAllPrint();

    // return the statement numbers of all ASSIGN statements
    std::unordered_set<int> getAllAssign();

    // return the statement numbers of all CALL statements
    std::unordered_set<int> getAllCall();

    // return the statement numbers of all WHILE statements
    std::unordered_set<int> getAllWhile();

    // return the statement numbers of all IF statements
    std::unordered_set<int> getAllIf();

    int getFollowing(int statementNumber, std::string statementType);

    int getFollowed(int statementNumber, std::string statementType);

    std::set<int> getStatementsModifying(std::string variableName, std::string statementType);

    std::set<std::string> getVariablesModifiedBy(int statementNumber, std::string statementType);

    std::set<int> getStatementsUsing(std::string variableName, std::string statementType);

    std::set<std::string> getVariablesUsedBy(int statementNumber, std::string statementType);

    std::set<int> PKBReader::getAllStatementsModifying(std::string variableName);

    std::set<int> PKBReader::getAllStatementsUsing(std::string variableName);

    std::set<std::string> PKBReader::getAllUsedVariables();

    std::set<std::string> PKBReader::getAllModifiedVariables();

    std::set<int> PKBReader::getAllUsingStatements();

    std::set<int> PKBReader::getAllModifyingStatements();


private:
    DesignEntitiesStorage designEntitiesStorage;
    FollowsStorage followsStorage;
    ModifiesStorage modifiesStorage;
    ParentStorage parentStorage;
    StatementStorage statementStorage;
    UsesStorage usesStorage;
};

#endif // PKBREADER_H
