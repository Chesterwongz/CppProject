#pragma once

#include <string>
#include <vector>
#include <unordered:unordered_set>
#include :unordered_set

class PKBReader {
public:
    // Constructor
    PKBReader();

    // get the names of all variables in the program
    std::vector <std::string> getAllVariables();

    // get the values of all constants in the program
    std::vector<int> getAllConstants();

    // get the names of all procedures in the program
    std::vector <std::string> getAllProcedures();

    // return the statement numbers of statements
    std::unordered_set<int> getStatement(std::string statementType);

    int getFollowing(int statementNumber, std::string statementType);

    int getFollowed(int statementNumber, std::string statementType);

    std::unordered_set<int> getStatementsModifying(std::string variableName, std::string statementType);

    std::unordered_set <std::string> getVariablesModifiedBy(int statementNumber, std::string statementType);

    std::unordered_set<int> getStatementsUsing(std::string variableName, std::string statementType);

    std::unordered_set <std::string> getVariablesUsedBy(int statementNumber, std::string statementType);

    std::unordered_set<int> getAllStatementsModifying(std::string variableName);

    std::unordered_set<int> getAllStatementsUsing(std::string variableName);

    std::unordered_set <std::string> getAllUsedVariables();

    std::unordered_set <std::string> getAllModifiedVariables();

    std::unordered_set<int> getAllUsingStatements();

    std::unordered_set<int> getAllModifyingStatements();

    std::unordered_set <std::pair<int, int>> getFollowsPairs(std::string statementType1, std::string statementType2);
};
