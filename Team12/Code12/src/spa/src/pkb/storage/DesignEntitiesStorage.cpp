#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

class DesignEntitiesStorage {
public:
    // Constructor
    DesignEntitiesStorage() {}

    // Setter for variables
    void setVariable(const std::string& variableName, int statementNumber) {
        if (!variableData.count(variableName)) {
            variableData[variableName] = std::vector<int>{ statementNumber };
        }
        else {
            auto& statements = variableData[variableName];
            auto it = std::lower_bound(statements.begin(), statements.end(), statementNumber);
            if (it == statements.end() || *it != statementNumber) {
                statements.insert(it, statementNumber);
            }
        }
    }

    // Setter for constants
    void setConstant(int constantValue, int statementNumber) {
        if (!constantData.count(constantValue)) {
            constantData[constantValue] = std::vector<int>{ statementNumber };
        }
        else {
            auto& statements = constantData[constantValue];
            auto it = std::lower_bound(statements.begin(), statements.end(), statementNumber);
            if (it == statements.end() || *it != statementNumber) {
                statements.insert(it, statementNumber);
            }
        }
    }

    // Setter for procedures
    void setProcedure(const std::string& procedureName, int startStatement) {
        procedureData[procedureName] = startStatement;
    }

    // Get all variables
    std::vector<std::string> getAllVariables() {
        std::vector<std::string> variables;
        for (const auto& entry : variableData) {
            variables.push_back(entry.first);
        }
        return variables;
    }

    // Get all constants
    std::vector<int> getAllConstants() {
        std::vector<int> constants;
        for (const auto& entry : constantData) {
            constants.push_back(entry.first);
        }
        return constants;
    }

    // Get all procedures
    std::vector<std::string> getAllProcedures() {
        std::vector<std::string> procedures;
        for (const auto& entry : procedureData) {
            procedures.push_back(entry.first);
        }
        return procedures;
    }

    // Get variables on a statement
    std::vector<std::string> getVariablesOnStatement(int statementNumber) {
        std::vector<std::string> variables;
        for (const auto& entry : variableData) {
            if (std::binary_search(entry.second.begin(), entry.second.end(), statementNumber)) {
                variables.push_back(entry.first);
            }
        }
        return variables;
    }

    // Get statements of a variable
    std::vector<int> getStatementsOfVariable(const std::string& variableName) {
        if (variableData.count(variableName)) {
            return variableData[variableName];
        }
        else {
            return std::vector<int>();
        }
    }

    // Get constants on a statement
    std::vector<int> getConstantsOnStatement(int statementNumber) {
        std::vector<int> constants;
        for (const auto& entry : constantData) {
            if (std::binary_search(entry.second.begin(), entry.second.end(), statementNumber)) {
                constants.push_back(entry.first);
            }
        }
        return constants;
    }

    // Get statements of a constant
    std::vector<int> getStatementsOfConstant(int constantValue) {
        if (constantData.count(constantValue)) {
            return constantData[constantValue];
        }
        else {
            return std::vector<int>();
        }
    }

    // Get procedures on a statement
    std::vector<std::string> getProceduresOnStatement(int statementNumber) {
        std::vector<std::string> procedures;
        for (const auto& entry : procedureData) {
            if (entry.second == statementNumber) {
                procedures.push_back(entry.first);
            }
        }
        return procedures;
    }

    // Get the starting statement of a procedure
    int getStartingStatementOfProcedure(const std::string& procedureName) {
        if (procedureData.count(procedureName)) {
            return procedureData[procedureName];
        }
        else {
            return -1; // Return -1 if procedure not found
        }
    }

private:
    // Data structure for variables (variable name -> statement numbers)
    std::map<std::string, std::vector<int>> variableData;

    // Data structure for constants (constant value -> statement numbers)
    std::map<int, std::vector<int>> constantData;

    // Data structure for procedures (procedure name -> starting statement)
    std::map<std::string, int> procedureData;
};
