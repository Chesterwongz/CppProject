#include "DesignEntitiesStorage.h"

#include <algorithm>
#include <iostream>

// Constructor
DesignEntitiesStorage::DesignEntitiesStorage() = default;

// Setter for variables
void DesignEntitiesStorage::setVariable(const std::string& variableName) {
    variableData.insert(variableName);
}

// Setter for constants
void DesignEntitiesStorage::setConstant(const std::string& constantValue) {
    constantData.insert(constantValue);
}

// Setter for procedures
void DesignEntitiesStorage::setProcedure(const std::string& procedureName, int startStatement) {
    procedureData[procedureName] = startStatement;
}

// Get all variables
std::set<std::string> DesignEntitiesStorage::getAllVariables() {
    return variableData;
}

// Get all constants
std::set<std::string> DesignEntitiesStorage::getAllConstants() {
    return constantData;
}

// Get all procedures
std::set<std::string> DesignEntitiesStorage::getAllProcedures() {
    std::set<std::string> procedures;
    for (const auto& entry : procedureData) {
        procedures.insert(entry.first);
    }
    return procedures;
}

// Get procedure starting on a statement
std::string DesignEntitiesStorage::getProcedureStartingOnStatement(int statementNumber) {
    std::set<std::string> procedures;
    for (const auto& entry : procedureData) {
        if (entry.second == statementNumber) {
            return entry.first;
        }
    }
}

// Get the starting statement of a procedure
int DesignEntitiesStorage::getStartingStatementOfProcedure(const std::string& procedureName) {
    if (procedureData.count(procedureName)) {
        return procedureData[procedureName];
    }
    else {
        return -1;
    }
}