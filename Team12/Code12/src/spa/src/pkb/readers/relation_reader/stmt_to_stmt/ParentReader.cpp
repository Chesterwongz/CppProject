#include "ParentReader.h"

std::vector<std::string> ParentReader::getImmediateChildrenOf(int s1,
    StmtType stmtType) {
  return reader.getDirectS2ByS1(s1, stmtType);
}

std::vector<std::string> ParentReader::getImmediateParentOf(int s2, StmtType stmtType) {
  return reader.getDirectS1ByS2(s2, stmtType);
}

bool ParentReader::isParent(int stmt1, int stmt2) {
  return reader.hasDirectRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
ParentReader::getParentChildPairs(StmtType stmtType1, StmtType stmtType2) {
  return reader.getDirectS1AndS2Pairs(stmtType1, stmtType2);
}

bool ParentReader::hasParents() {
  return reader.hasDirectS1AndS2Pairs();
}

// ================================== ParentT ==================================

std::vector<std::string> ParentReader::getChildrenStarOf(int s1, StmtType stmtType) {
  return reader.getTransitiveS2ByS1(s1, stmtType);
}

std::vector<std::string> ParentReader::getParentStarOf(int s2, StmtType stmtType) {
  return reader.getTransitiveS1ByS2(s2, stmtType);
}

bool ParentReader::isParentStar(int stmt1, int stmt2) {
  return reader.hasTransitiveRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
ParentReader::getParentChildStarPairs(StmtType stmtType1, StmtType stmtType2) {
  return reader.getTransitiveS1AndS2Pairs(stmtType1, stmtType2);
}

bool ParentReader::hasParentsT() {
  return reader.hasDirectS1AndS2Pairs();
}
