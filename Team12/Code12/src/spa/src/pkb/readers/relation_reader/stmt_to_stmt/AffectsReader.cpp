#include "AffectsReader.h"

void AffectsReader::processAffectsPairs(
    std::vector<std::pair<std::string, std::string>>& result,
    bool findOnlyFirst) {
  const auto assignStmts = stmtStore.getAllStmtsOf(StmtType::ASSIGN);

  for (const auto& assign : assignStmts) {
    if (!modifiesSStore.hasDirectSuccessors(assign)) continue;
    std::unordered_set<std::string> done;
    std::string v = *modifiesSStore.getDirectSuccessors(assign).begin();

    findAffectsPairs(assign, assign, v, done, result);

    if (findOnlyFirst && !result.empty()) {
      break;
    }
  }
}

std::vector<std::pair<std::string, std::string>>
AffectsReader::getAffectsPairs() {
  if (affectsCache.getIsComplete()) {
    auto stmtFilters = stmtStore.getStmtStmtFilterPredicates(StmtType::ASSIGN,
                                                             StmtType::ASSIGN);
    return CollectionUtils::intIntMapSetToStrPairVector(
        affectsCache.getDirectSuccessorMap(), stmtFilters);
  }
  std::vector<std::pair<std::string, std::string>> result;
  processAffectsPairs(result, false);
  affectsCache.setIsComplete();
  return result;
}

void AffectsReader::findAffectsPairs(
    int originalStmt, int currentStmt, const std::string& variable,
    std::unordered_set<std::string>& done,
    std::vector<std::pair<std::string, std::string>>& result) {
  done.insert(std::to_string(currentStmt));
  if (!nextStore.hasDirectSuccessors(currentStmt)) return;
  for (const auto& nextStmt : nextStore.getDirectSuccessors(currentStmt)) {
    if (nextStmt == originalStmt &&
        usesSStore.hasDirectRelation(nextStmt, variable)) {
      affectsCache.addRelation(originalStmt, nextStmt);
      result.emplace_back(std::to_string(originalStmt),
                          std::to_string(nextStmt));
    }

    if (done.count(std::to_string(nextStmt))) {
      continue;
    }

    if (stmtStore.hasStmt(nextStmt, StmtType::ASSIGN) &&
        usesSStore.hasDirectRelation(nextStmt, variable)) {
      affectsCache.addRelation(originalStmt, nextStmt);
      result.emplace_back(std::to_string(originalStmt),
                          std::to_string(nextStmt));
    }

    bool isValidType = isCallReadAssign(nextStmt);

    if (isValidType && modifiesSStore.hasDirectRelation(nextStmt, variable)) {
      continue;
    }

    findAffectsPairs(originalStmt, nextStmt, variable, done, result);
  }
}

bool AffectsReader::isAffects(int s1, int s2) {
  if (s1 == common::WILDCARD_STMT_NUM) {
    return getAffectedBy(s2, StmtType::ASSIGN).empty();
  } else if (s2 == common::WILDCARD_STMT_NUM) {
    return getAffects(s1, StmtType::ASSIGN).empty();
  }
  if (!nextStore.hasRelationT(s1, s2) ||
      !(stmtStore.hasStmt(s1, StmtType::ASSIGN) &&
        stmtStore.hasStmt(s2, StmtType::ASSIGN)) ||
      !usesSStore.hasDirectSuccessors(s2)) {
    return false;
  }

  if (affectsCache.hasDirectRelation(s1, s2)) {
    return true;
  }

  if (affectsCache.getIsComplete() && !affectsCache.hasDirectRelation(s1, s2)) {
    return false;
  }
  std::vector<std::string> affectingStmts = getAffects(s1, StmtType::ASSIGN);
  return std::find(affectingStmts.begin(), affectingStmts.end(),
                   std::to_string(s2)) != affectingStmts.end();
}

std::vector<std::string> AffectsReader::getAffects(int s1, StmtType stmtType) {
  if (s1 == common::WILDCARD_STMT_NUM) {
    return getAllAffectsS2();
  }
  std::vector<std::string> result;
  std::vector<std::pair<std::string, std::string>> resultPairs;
  std::unordered_set<std::string> done;

  if (!stmtStore.hasStmt(s1, StmtType::ASSIGN)) {
    return result;
  }

  if (affectsCache.getIsComplete() && affectsCache.hasDirectSuccessors(s1)) {
    auto stmtFilter = stmtStore.getStmtFilterPredicate(StmtType::ASSIGN);
    return CollectionUtils::intSetToStrVector(
        affectsCache.getDirectSuccessors(s1), stmtFilter);
  }

  const std::string& v = *modifiesSStore.getDirectSuccessors(s1).begin();

  findAffectsPairs(s1, s1, v, done, resultPairs);

  for (const auto& pair : resultPairs) {
    result.emplace_back(pair.second);
    affectsCache.addRelation(stoi(pair.first), stoi(pair.second));
  }

  return result;
}

std::vector<std::string> AffectsReader::getAffectedBy(int s2,
                                                      StmtType stmtType) {
  if (s2 == common::WILDCARD_STMT_NUM) {
    return getAllAffectsS1();
  }
  std::vector<std::string> result;
  std::unordered_set<std::string> usedVariables;
  if (!stmtStore.hasStmt(s2, StmtType::ASSIGN)) {
    return result;
  }
  if (affectsCache.getIsComplete() && affectsCache.hasDirectAncestors(s2)) {
    auto stmtFilter = stmtStore.getStmtFilterPredicate(StmtType::ASSIGN);
    return CollectionUtils::intSetToStrVector(
        affectsCache.getDirectAncestors(s2), stmtFilter);
  }

  if (usesSStore.hasDirectSuccessors(s2)) {
    usedVariables = usesSStore.getDirectSuccessors(s2);
    std::unordered_set<int> allModifyingStmts;
    for (const std::string& var : usedVariables) {
      if (modifiesSStore.hasDirectAncestors(var)) {
        std::unordered_set<int> modifyingStmts =
            modifiesSStore.getDirectAncestors(var);
        for (int stmt : modifyingStmts) {
          allModifyingStmts.insert(stmt);
        }
      }
    }

    for (int stmt : allModifyingStmts) {
      if (isAffects(stmt, s2)) {
        result.emplace_back(std::to_string(stmt));
        affectsCache.addRelation(stmt, s2);
      }
    }
  }

  return result;
}

bool AffectsReader::isCallReadAssign(int statementNumber) {
  return stmtStore.hasStmt(statementNumber, StmtType::ASSIGN) ||
         stmtStore.hasStmt(statementNumber, StmtType::READ) ||
         stmtStore.hasStmt(statementNumber, StmtType::CALL);
}

bool AffectsReader::hasAffects() {
  if (affectsCache.getIsComplete()) {
    return affectsCache.getDirectSuccessorMap().empty();
  }
  std::vector<std::pair<std::string, std::string>> result;
  processAffectsPairs(result, true);
  return !result.empty();
}

std::vector<std::string> AffectsReader::getUniqueAffects(
    const std::function<
        std::string(const std::pair<std::string, std::string>&)>& extractor) {
  const auto affectsPairs = getAffectsPairs();
  std::unordered_set<std::string> resultSet;

  for (const auto& pair : affectsPairs) {
    resultSet.insert(extractor(pair));
  }

  return {resultSet.begin(), resultSet.end()};
}

std::vector<std::string> AffectsReader::getAllAffectsS1() {
  return getUniqueAffects([](const std::pair<std::string, std::string>& pair) {
    return pair.first;
  });
}

std::vector<std::string> AffectsReader::getAllAffectsS2() {
  return getUniqueAffects([](const std::pair<std::string, std::string>& pair) {
    return pair.second;
  });
}
