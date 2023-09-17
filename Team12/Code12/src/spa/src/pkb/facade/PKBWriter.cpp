#include "PKBWriter.h"

void PKBWriter::setFollowsRelationship(int statementNumber, int followingStatement) {
    storage.followsStorage.setFollows(statementNumber, followingStatement);
}

void PKBWriter::setModifiesRelationship(const std::string& variableName, int statementNumber) {
    storage.modifiesStorage.setVariableModification(variableName, statementNumber);
}

void PKBWriter::setParentRelationship(int statementNumber, int childStatement) {
    storage.parentStorage.setParent(statementNumber, childStatement);
}

void PKBWriter::setUsesRelationship(const std::string& variableName, int statementNumber) {
    storage.usesStorage.setVariableUsage(variableName, statementNumber);
}

void PKBWriter::setStatement(int statementNumber, StmtType statementType) {
    storage.statementStorage.setStatement(statementNumber, statementType);
}

void PKBWriter::setVariable(const std::string& variableName) {
    storage.designEntitiesStorage.setVariable(variableName);
}

void PKBWriter::setConstant(const std::string& constantValue) {
    storage.designEntitiesStorage.setConstant(constantValue);
}

void PKBWriter::setProcedure(const std::string& procedureName, int startStatement) {
    storage.designEntitiesStorage.setProcedure(procedureName, startStatement);
}

void PKBWriter::setAssignPattern(int statementNumber, const std::string &varName, const std::string &expr) {}

void PKBWriter::setWhilePattern(int statementNumber, const std::string &varName) {}

void PKBWriter::setIfPattern(int statementNumber, const std::string &varName) {}
