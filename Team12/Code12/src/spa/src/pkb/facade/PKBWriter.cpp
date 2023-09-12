#include "PKBWriter.h"

//not complete
PKBWriter::PKBWriter() = default;

void PKBWriter::setFollowsRelationship(int statementNumber, int followingStatement) {
    followsStorage.setFollows(statementNumber, followingStatement);
}

void PKBWriter::setModifiesRelationship(const std::string& variableName, int statementNumber) {
    modifiesStorage.setVariableModification(variableName, statementNumber);
}

void PKBWriter::setParentRelationship(int statementNumber, int childStatement) {
    parentStorage.setParent(statementNumber, childStatement);
}

void PKBWriter::setUsesRelationship(const std::string& variableName, int statementNumber) {
    usesStorage.setVariableUsage(variableName, statementNumber);
}

void PKBWriter::setStatement(int statementNumber, StmtType statementType) {
    statementStorage.setStatement(statementNumber, statementType);
}

void PKBWriter::setVariable(const std::string& variableName) {
    designEntitiesStorage.setVariable(variableName);
}

void PKBWriter::setConstant(const std::string& constantValue) {
    designEntitiesStorage.setConstant(constantValue);
}

void PKBWriter::setProcedure(const std::string& procedureName, int startStatement) {
    designEntitiesStorage.setProcedure(procedureName, startStatement);
}