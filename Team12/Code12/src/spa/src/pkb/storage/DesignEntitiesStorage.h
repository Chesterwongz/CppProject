#pragma once

#include <unordered_set>
#include <string>
#include <unordered_map>

class DesignEntitiesStorage {
public:
    DesignEntitiesStorage();

    void setVariable(const std::string& variableName, int statementNumber);

    void setConstant(int constantValue, int statementNumber);

    void setProcedure(const std::string& procedureName, int startStatement);

    std::unordered_set<std::string> getAllVariables();

    std::unordered_set<int> getAllConstants();

    std::unordered_set<std::string> getAllProcedures();

    std::unordered_set<std::string> getVariablesOnStatement(int statementNumber);

    std::unordered_set<int> getStatementsOfVariable(const std::string& variableName);

    std::unordered_set<int> getConstantsOnStatement(int statementNumber);

    std::unordered_set<int> getStatementsOfConstant(int constantValue);

    std::unordered_set<std::string> getProceduresOnStatement(int statementNumber);

    int getStartingStatementOfProcedure(const std::string& procedureName);

private:
    // Data structure for variables (variable name -> statement numbers)
    std::unordered_map<std::string, std::unordered_set<int>> variableData;

    // Data structure for constants (constant value -> statement numbers)
    std::unordered_map<int, std::unordered_set<int>> constantData;

    // Data structure for procedures (procedure name -> starting statement)
    std::unordered_map<std::string, int> procedureData;
};
