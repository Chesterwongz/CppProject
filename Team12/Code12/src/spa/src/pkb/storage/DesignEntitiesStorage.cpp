#include "DesignEntitiesStorage.h"

#include <algorithm>
#include <iostream>

// Constructor
DesignEntitiesStorage::DesignEntitiesStorage() {}

// Setter for variables
void DesignEntitiesStorage::setVariable(const std::string& variableName) {
    variableData.insert(variableName);
}

// Setter for constants
void DesignEntitiesStorage::setConstant(int constantValue) {
    constantData.insert(constantValue);
}

// Setter for procedures
void DesignEntitiesStorage::setProcedure(const std::string& procedureName, int startStatement) {
    procedureData[procedureName] = startStatement;
}

// Get all variables
std::unordered_set<std::string> DesignEntitiesStorage::getAllVariables() {
    return variableData;
}

// Get all constants
std::unordered_set<int> DesignEntitiesStorage::getAllConstants() {
    return constantData;
}

// Get all procedures
std::unordered_set<std::string> DesignEntitiesStorage::getAllProcedures() {
    std::unordered_set<std::string> procedures;
    for (const auto& entry : procedureData) {
        procedures.insert(entry.first);
    }
    return procedures;
}

// Get procedures on a statement
std::unordered_set<std::string> DesignEntitiesStorage::getProceduresOnStatement(int statementNumber) {
    std::unordered_set<std::string> procedures;
    for (const auto& entry : procedureData) {
        if (entry.second == statementNumber) {
            procedures.insert(entry.first);
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
