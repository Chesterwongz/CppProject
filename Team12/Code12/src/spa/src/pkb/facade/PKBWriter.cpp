#include "PKBWriter.h"

//not complete
PKBWriter::PKBWriter() {}

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

void PKBWriter::setStatement(const std::string& statementType, int statementNumber) {
    statementStorage.setStatement(statementType, statementNumber);
}
