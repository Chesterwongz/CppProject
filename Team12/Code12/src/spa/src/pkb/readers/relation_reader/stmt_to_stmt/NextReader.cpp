#include "NextReader.h"

std::vector<std::string> NextReader::getPrevStmts(int stmt2,
                                                  StmtType stmtType1) {
  if (!stmtStore.hasStmtType(stmtType1) ||
      !nextStore.hasDirectAncestors(stmt2)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType1);

  const auto& rawRes = nextStore.getDirectAncestors(stmt2);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

std::vector<std::string> NextReader::getNextStmts(int stmt1,
                                                  StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType2) ||
      !nextStore.hasDirectSuccessors(stmt1)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType2);

  const auto& rawRes = nextStore.getDirectSuccessors(stmt1);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
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

  const auto& rawRes = nextStore.getDirectRelations();

  return CollectionUtils::transformMapSetABToVectorUV<int, int, std::string,
                                                      std::string>(
      rawRes, CollectionUtils::getIntToStrMapperPair(), stmtFilters);
}

// =================================== NextT ===================================

std::vector<std::string> NextReader::getPrevTStmts(int stmt2,
                                                   StmtType stmtType1) {
  if (!stmtStore.hasStmtType(stmtType1) || !nextStore.hasAncestorsT(stmt2)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType1);

  const auto& allPrevT = nextStore.getAncestorsT(stmt2);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      allPrevT, CollectionUtils::intToStrMapper, stmtFilter);
}

std::vector<std::string> NextReader::getNextTStmts(int stmt1,
                                                   StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType2) || !nextStore.hasSuccessorsT(stmt1)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType2);

  const auto& allNextT = nextStore.getSuccessorsT(stmt1);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      allNextT, CollectionUtils::intToStrMapper, stmtFilter);
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

  const auto& rawRes = nextStore.getRelationsT();

  return CollectionUtils::transformMapSetABToVectorUV<int, int, std::string,
                                                      std::string>(
      rawRes, CollectionUtils::getIntToStrMapperPair(), stmtFilters);
}
