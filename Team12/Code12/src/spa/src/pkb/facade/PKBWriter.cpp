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

void PKBWriter::setReadStatement(int statementNumber) {
    statementStorage.setReadStatement(statementNumber);
}

void PKBWriter::setPrintStatement(int statementNumber) {
    statementStorage.setPrintStatement(statementNumber);
}

void PKBWriter::setAssignStatement(int statementNumber) {
    statementStorage.setAssignStatement(statementNumber);
}

void PKBWriter::setCallStatement(int statementNumber) {
    statementStorage.setCallStatement(statementNumber);
}

void PKBWriter::setIfStatement(int statementNumber) {
    statementStorage.setIfStatement(statementNumber);
}

void PKBWriter::setWhileStatement(int statementNumber) {
    statementStorage.setWhileStatement(statementNumber);
}