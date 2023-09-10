#include "DesignEntitiesStorage.h"

#include <algorithm>
#include <iostream>

// Constructor
DesignEntitiesStorage::DesignEntitiesStorage() {}

// Setter for variables
void DesignEntitiesStorage::setVariable(const std::string& variableName, int statementNumber) {
    variableData[variableName].insert(statementNumber);
}

// Setter for constants
void DesignEntitiesStorage::setConstant(int constantValue, int statementNumber) {
    constantData[constantValue].insert(statementNumber);
}

// Setter for procedures
void DesignEntitiesStorage::setProcedure(const std::string& procedureName, int startStatement) {
    procedureData[procedureName] = startStatement;
}

// Get all variables
std::unordered_set<std::string> DesignEntitiesStorage::getAllVariables() {
    std::unordered_set<std::string> variables;
    for (const auto& entry : variableData) {
        variables.insert(entry.first);
    }
    return variables;
}

// Get all constants
std::unordered_set<int> DesignEntitiesStorage::getAllConstants() {
    std::unordered_set<int> constants;
    for (const auto& entry : constantData) {
        constants.insert(entry.first);
    }
    return constants;
}

// Get all procedures
std::unordered_set<std::string> DesignEntitiesStorage::getAllProcedures() {
    std::unordered_set<std::string> procedures;
    for (const auto& entry : procedureData) {
        procedures.insert(entry.first);
    }
    return procedures;
}

// Get variables on a statement
std::unordered_set<std::string> DesignEntitiesStorage::getVariablesOnStatement(int statementNumber) {
    std::unordered_set<std::string> variables;
    for (const auto& entry : variableData) {
        if (entry.second.count(statementNumber)) {
            variables.insert(entry.first);
        }
    }
    return variables;
}

// Get statements of a variable
std::unordered_set<int> DesignEntitiesStorage::getStatementsOfVariable(const std::string& variableName) {
    return variableData[variableName];
}

// Get constants on a statement
std::unordered_set<int> DesignEntitiesStorage::getConstantsOnStatement(int statementNumber) {
    std::unordered_set<int> constants;
    for (const auto& entry : constantData) {
        if (entry.second.count(statementNumber)) {
            constants.insert(entry.first);
        }
    }
    return constants;
}

// Get statements of a constant
std::unordered_set<int> DesignEntitiesStorage::getStatementsOfConstant(int constantValue) {
    return constantData[constantValue];
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
int DesignEntitiesStorage::getStartingStatementOfProcedure(const std::string& procedureName) {
    if (procedureData.count(procedureName)) {
        return procedureData[procedureName];
    }
    else {
        return -1; // Return -1 if procedure not found
    }
}
