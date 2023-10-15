#include "PatternWriter.h"

void PatternWriter::addAssignPattern(const std::string& varName,
                                     const std::string& rpn, int stmtNum) {
  patternStorage.setAssignPattern(varName, rpn, stmtNum);
}

void PatternWriter::addWhilePattern(int stmtNum, const std::string& varName) {
  patternStorage.setWhilePattern(stmtNum, varName);
}

void PatternWriter::addIfPattern(int stmtNum, const std::string& varName) {
  patternStorage.setIfPattern(stmtNum, varName);
}
