#include "NextReader.h"

std::vector<std::string> NextReader::getPrevStmts(StmtType stmtType1, int stmt2 = common::DEFAULT_STMT_NUM) {
  return reader.getDirectS1ByS2(stmtType1, stmt2);
}

std::vector<std::string> NextReader::getNextStmts(StmtType stmtType2, int stmt1 = common::DEFAULT_STMT_NUM) {
  return reader.getDirectS2ByS1(stmtType2, stmt1);
}

bool NextReader::isNext(int stmt1, int stmt2) {
  return reader.hasDirectRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextPairs(
    StmtType stmtType1, StmtType stmtType2) {
  return reader.getDirectS1AndS2Pairs(stmtType1, stmtType2);
}

// =================================== NextT ===================================

std::vector<std::string> NextReader::getPrevTStmts(StmtType stmtType1, int stmt2 = common::DEFAULT_STMT_NUM) {
  return reader.getTransitiveS1ByS2(stmtType1, stmt2);
}

std::vector<std::string> NextReader::getNextTStmts(StmtType stmtType2, int stmt1 = common::DEFAULT_STMT_NUM) {
  return reader.getTransitiveS2ByS1(stmtType2, stmt1);
}

bool NextReader::isNextT(int stmt1, int stmt2) {
  return reader.hasTransitiveRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextTPairs(
    StmtType stmtType1, StmtType stmtType2) {
  return reader.getTransitiveS1AndS2Pairs(stmtType1, stmtType2);
}
