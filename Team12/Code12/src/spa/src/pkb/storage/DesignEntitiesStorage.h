#pragma once

#include <unordered_set>
#include <string>
#include <unordered_map>

class DesignEntitiesStorage {
public:
    DesignEntitiesStorage();

    void setVariable(const std::string& variableName);

    void setConstant(int constantValue);

    void setProcedure(const std::string& procedureName, int startStatement);

    std::unordered_set<std::string> getAllVariables();

    std::unordered_set<int> getAllConstants();

    std::unordered_set<std::string> getAllProcedures();

    std::unordered_set<std::string> getProceduresOnStatement(int statementNumber);

    int getStartingStatementOfProcedure(const std::string& procedureName);

private:
    // Data structure for variables (variable name -> first statement number)
    std::unordered_set<std::string> variableData;

    // Data structure for constants (constant value -> first statement number)
    std::unordered_set<int> constantData;

    // Data structure for procedures (procedure name -> starting statement)
    std::unordered_map<std::string, int> procedureData;
};