#pragma once

#include <set>
#include <string>
#include <unordered_map>

class DesignEntitiesStorage {
public:
    DesignEntitiesStorage();

    void setVariable(const std::string& variableName);

    void setConstant(const std::string& constantValue);

    void setProcedure(const std::string& procedureName, int startStatement);

    std::set<std::string> getAllVariables();

    std::set<std::string> getAllConstants();

    std::set<std::string> getAllProcedures();

    std::set<std::string> getProceduresOnStatement(int statementNumber);

    int getStartingStatementOfProcedure(const std::string& procedureName);

private:
    std::set<std::string> variableData;

    std::set<std::string> constantData;

    // Data structure for procedures (procedure name -> starting statement)
    std::unordered_map<std::string, int> procedureData;
};