#include "ParentReader.h"

std::vector<std::string> ParentReader::getImmediateChildrenOf(
    StmtType stmtType, int stmt = common::DEFAULT_STMT_NUM) {
  return reader.getDirectS2ByS1(stmtType, stmt);
}

std::vector<std::string> ParentReader::getImmediateParentOf(StmtType stmtType, int stmt = common::DEFAULT_STMT_NUM) {
  return reader.getDirectS1ByS2(stmtType, stmt);
}

bool ParentReader::isParent(int stmt1, int stmt2) {
  return reader.hasDirectRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
ParentReader::getParentChildPairs(StmtType stmtType1, StmtType stmtType2) {
  return reader.getDirectS1AndS2Pairs(stmtType1, stmtType2);
}

// ================================== ParentT ==================================

std::vector<std::string> ParentReader::getChildrenStarOf(StmtType stmtType, int stmt = common::DEFAULT_STMT_NUM) {
  return reader.getTransitiveS2ByS1(stmtType, stmt);
}

std::vector<std::string> ParentReader::getParentStarOf(StmtType stmtType, int stmt = common::DEFAULT_STMT_NUM) {
  return reader.getTransitiveS1ByS2(stmtType, stmt);
}

bool ParentReader::isParentStar(int stmt1, int stmt2) {
  return reader.hasTransitiveRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
ParentReader::getParentChildStarPairs(StmtType stmtType1, StmtType stmtType2) {
  return reader.getTransitiveS1AndS2Pairs(stmtType1, stmtType2);
}
