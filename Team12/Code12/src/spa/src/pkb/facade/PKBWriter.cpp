#include "PKBWriter.h"

void PKBWriter::setFollowsRelationship(int statementNumber, int followingStatement) {
    storage.setFollows(statementNumber, followingStatement);
}

void PKBWriter::setModifiesRelationship(const std::string& variableName, int statementNumber) {
    storage.setVariableModification(variableName, statementNumber);
}

void PKBWriter::setParentRelationship(int statementNumber, int childStatement) {
    storage.setParent(statementNumber, childStatement);
}

void PKBWriter::setParentStarRelationship(int statementNumber, int childStatement) {
    storage.setParentStar(statementNumber, childStatement);
}

void PKBWriter::setUsesRelationship(const std::string& variableName, int statementNumber) {
    storage.setVariableUsage(variableName, statementNumber);
}

void PKBWriter::setStatement(int statementNumber, StmtType statementType) {
    storage.setStatement(statementNumber, statementType);
}

void PKBWriter::setVariable(const std::string& variableName) {
    storage.setVariable(variableName);
}

void PKBWriter::setConstant(const std::string& constantValue) {
    storage.setConstant(constantValue);
}

void PKBWriter::setProcedure(const std::string& procedureName, int startStatement) {
    storage.setProcedure(procedureName, startStatement);
}

void PKBWriter::setAssignPattern(const std::string& variableName, const std::string& rpn, int statementNumber) {
    storage.setAssignPattern(variableName, rpn, statementNumber);
}
void PKBWriter::setWhilePattern(int statementNumber, const std::string &varName) {}

void PKBWriter::setIfPattern(int statementNumber, const std::string &varName) {}

void PKBWriter::setUsesRelationship(const std::string &variableName, const std::string &procedureName) {}

void PKBWriter::setModifiesRelationship(const std::string &variableName, const std::string &procedureName) {}

void PKBWriter::setCallsRelationship(const std::string &callerProc, const std::string &calleeProc) {}

void PKBWriter::setCallsStarRelationship(const std::string &callerProc, const std::string &calleeProc) {}
