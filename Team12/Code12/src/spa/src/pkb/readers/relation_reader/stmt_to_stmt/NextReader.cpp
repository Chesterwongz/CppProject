#include "NextReader.h"

std::vector<std::string> NextReader::getPrevStmts(int s2, StmtType type1) {
  return reader.getDirectS1ByS2(s2, type1);
}

std::vector<std::string> NextReader::getNextStmts(int s1, StmtType type2) {
  return reader.getDirectS2ByS1(s1, type2);
}

bool NextReader::isNext(int s1, int s2) {
  return reader.hasDirectRelation(s1, s2);
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextPairs(
    StmtType type1, StmtType type2) {
  return reader.getDirectS1AndS2Pairs(type1, type2);
}

// =================================== NextT ===================================

std::vector<std::string> NextReader::getPrevTStmts(int s2, StmtType type1) {
  return reader.getTransitiveS1ByS2(s2, type1);
}

std::vector<std::string> NextReader::getNextTStmts(int s1, StmtType type2) {
  return reader.getTransitiveS2ByS1(s1, type2);
}

bool NextReader::isNextT(int s1, int s2) {
  return reader.hasTransitiveRelation(s1, s2);
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextTPairs(
    StmtType type1, StmtType type2) {
  return reader.getTransitiveS1AndS2Pairs(type1, type2);
}
