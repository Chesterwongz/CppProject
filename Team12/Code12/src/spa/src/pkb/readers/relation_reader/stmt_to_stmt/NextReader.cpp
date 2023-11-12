#include "NextReader.h"

std::vector<std::string> NextReader::getPrevStmts(int stmt2,
                                                  StmtType stmtType1) {
  return reader.getDirectS1ByS2(stmt2, stmtType1);
}

std::vector<std::string> NextReader::getNextStmts(int stmt1,
                                                  StmtType stmtType2) {
  return reader.getDirectS2ByS1(stmt1, stmtType2);
}

bool NextReader::isNext(int stmt1, int stmt2) {
  return reader.hasDirectRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextPairs(
    StmtType stmtType1, StmtType stmtType2) {
  return reader.getDirectS1AndS2Pairs(stmtType1, stmtType2);
}

bool NextReader::hasNext() {
  return stmtStore.hasStmt() && !nextStore.getDirectRelations().empty();
}

// =================================== NextT ===================================

std::vector<std::string> NextReader::getPrevTStmts(int stmt2,
                                                   StmtType stmtType1) {
  return reader.getTransitiveS1ByS2(stmt2, stmtType1);
}

std::vector<std::string> NextReader::getNextTStmts(int stmt1,
                                                   StmtType stmtType2) {
  return reader.getTransitiveS2ByS1(stmt1, stmtType2);
}

bool NextReader::isNextT(int stmt1, int stmt2) {
  return reader.hasTransitiveRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextTPairs(
    StmtType stmtType1, StmtType stmtType2) {
  return reader.getTransitiveS1AndS2Pairs(stmtType1, stmtType2);
}

bool NextReader::hasNextT() {
  return stmtStore.hasStmt() && !nextStore.getRelationsT().empty();
}
