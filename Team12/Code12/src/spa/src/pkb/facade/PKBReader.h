#ifndef PKBREADER_H
#define PKBREADER_H

#include <string>
#include <iostream>
#include <vector>
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

    // return the statement numbers of all READ statements
    std::vector<int> getAllRead();

    // return the statement numbers of all PRINT statements
    std::vector<int> getAllPrint();

    // return the statement numbers of all ASSIGN statements
    std::vector<int> getAllAssign();

    // return the statement numbers of all CALL statements
    std::vector<int> getAllCall();

    // return the statement numbers of all WHILE statements
    std::vector<int> getAllWhile();

    // return the statement numbers of all IF statements
    std::vector<int> getAllIf();

    int getFollowing(int statementNumber, std::string statementType);

    int getFollowed(int statementNumber, std::string statementType);

    std::vector<int> getStatementsModifying(std::string variableName, std::string statementType);

    std::vector<std::string> getVariablesModifiedBy(int statementNumber, std::string statementType);

    std::vector<int> PKBReader::getStatementsUsing(std::string variableName, std::string statementType);

    std::vector<std::string> PKBReader::getVariablesUsedBy(int statementNumber, std::string statementType);


private:
    DesignEntitiesStorage designEntitiesStorage;
    FollowsStorage followsStorage;
    ModifiesStorage modifiesStorage;
    ParentStorage parentStorage;
    StatementStorage statementStorage;
    UsesStorage usesStorage;
};

#endif // PKBREADER_H
