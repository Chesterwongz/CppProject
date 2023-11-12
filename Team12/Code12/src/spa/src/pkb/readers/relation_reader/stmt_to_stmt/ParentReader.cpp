#include "ParentReader.h"

std::vector<std::string> ParentReader::getImmediateChildrenOf(
    int stmt, StmtType stmtType) {
  return reader.getDirectS2ByS1(stmt, stmtType);
}

std::vector<std::string> ParentReader::getImmediateParentOf(int stmt,
                                                            StmtType stmtType) {
  return reader.getDirectS1ByS2(stmt, stmtType);
}

bool ParentReader::isParent(int stmt1, int stmt2) {
  return reader.hasDirectRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
ParentReader::getParentChildPairs(StmtType stmtType1, StmtType stmtType2) {
  return reader.getDirectS1AndS2Pairs(stmtType1, stmtType2);
}

bool ParentReader::hasParents() {
  return stmtStore.hasStmt() && !parentStore.getDirectRelations().empty();
}

// ================================== ParentT ==================================

std::vector<std::string> ParentReader::getChildrenStarOf(int stmt,
                                                         StmtType stmtType) {
  return reader.getTransitiveS2ByS1(stmt, stmtType);
}

std::vector<std::string> ParentReader::getParentStarOf(int stmt,
                                                       StmtType stmtType) {
  return reader.getTransitiveS1ByS2(stmt, stmtType);
}

bool ParentReader::isParentStar(int stmt1, int stmt2) {
  return reader.hasTransitiveRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
ParentReader::getParentChildStarPairs(StmtType stmtType1, StmtType stmtType2) {
  return reader.getTransitiveS1AndS2Pairs(stmtType1, stmtType2);
}

bool ParentReader::hasParentsT() {
  return stmtStore.hasStmt() && !parentStore.getRelationsT().empty();
}
