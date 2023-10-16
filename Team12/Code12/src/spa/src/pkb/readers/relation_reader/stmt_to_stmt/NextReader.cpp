#include "NextReader.h"

std::vector<std::string> NextReader::getPrevStmts(int stmt2,
                                                  StmtType stmtType1) {
  if (!stmtStore.hasStmtType(stmtType1)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType1);

  auto rawRes = nextStore.getDirectAncestorsOf(stmt2, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

std::vector<std::string> NextReader::getNextStmts(int stmt1,
                                                  StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType2)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType2);

  auto rawRes = nextStore.getDirectSuccessorsOf(stmt1, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

bool NextReader::isNext(int stmt1, int stmt2) {
  return nextStore.hasDirectRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextPairs(
    StmtType stmtType1, StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType1) || !stmtStore.hasStmtType(stmtType2)) {
    return {};
  }

  auto stmtFilters =
      stmtStore.getStmtStmtFilterPredicates(stmtType1, stmtType2);

  auto rawRes = nextStore.getDirectRelations(stmtFilters);

  return CollectionUtils::transformIntIntToStrStrVector(rawRes);
}

// =================================== NextT ===================================

std::vector<std::string> NextReader::getPrevTStmts(int stmt2,
                                                   StmtType stmtType1) {
  if (!stmtStore.hasStmtType(stmtType1)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType1);

  auto rawRes = nextStore.getAncestorsTOf(stmt2, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

std::vector<std::string> NextReader::getNextTStmts(int stmt1,
                                                   StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType2)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType2);

  auto rawRes = nextStore.getSuccessorsTOf(stmt1, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

bool NextReader::isNextT(int stmt1, int stmt2) {
  return nextStore.hasRelationT(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>> NextReader::getNextTPairs(
    StmtType stmtType1, StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType1) || !stmtStore.hasStmtType(stmtType2)) {
    return {};
  }

  auto stmtFilters =
      stmtStore.getStmtStmtFilterPredicates(stmtType1, stmtType2);

  auto rawRes = nextStore.getDirectRelations(stmtFilters);

  return CollectionUtils::transformIntIntToStrStrVector(rawRes);
}
