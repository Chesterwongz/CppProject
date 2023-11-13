#include "AffectsReader.h"

std::vector<std::pair<std::string, std::string>>
AffectsReader::getAffectsPairs() {
  if (affectsCache.getIsComplete()) {
    auto stmtFilters = stmtStore.getStmtStmtFilterPredicates(StmtType::ASSIGN,
                                                             StmtType::ASSIGN);
    return CollectionUtils::intIntMapSetToStrPairVector(
        affectsCache.getDirectSuccessorMap(), stmtFilters);
  }

  std::vector<std::pair<std::string, std::string>> result;

  const auto& assignStmts = stmtStore.getAllStmtsOf(StmtType::ASSIGN);

  for (const auto& assign : assignStmts) {
    if (!modifiesSStore.hasDirectSuccessors(assign)) continue;
    std::unordered_set<std::string> done;
    std::string v = *modifiesSStore.getDirectSuccessors(assign).begin();

    findAffectsPairs(assign, assign, v, done, result);
  }

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

bool AffectsReader::isAffects(int firstStmtNum, int secondStmtNum) {
  if (!nextStore.hasRelationT(firstStmtNum, secondStmtNum) ||
      !(stmtStore.hasStmt(firstStmtNum, StmtType::ASSIGN) &&
        stmtStore.hasStmt(secondStmtNum, StmtType::ASSIGN)) ||
      !usesSStore.hasDirectSuccessors(secondStmtNum)) {
    return false;
  }

  if (affectsCache.hasDirectRelation(firstStmtNum, secondStmtNum)) {
    return true;
  }

  if (affectsCache.getIsComplete() &&
      !affectsCache.hasDirectRelation(firstStmtNum, secondStmtNum)) {
    return false;
  }

  std::vector<std::string> affectingStmts =
      getAffects(firstStmtNum, StmtType::ASSIGN);
  return std::find(affectingStmts.begin(), affectingStmts.end(),
                   std::to_string(secondStmtNum)) != affectingStmts.end();
}

std::vector<std::string> AffectsReader::getAffects(int firstStmtNum,
                                                   StmtType stmtType) {
  std::vector<std::string> result;
  std::vector<std::pair<std::string, std::string>> resultPairs;
  std::unordered_set<std::string> done;

  if (!stmtStore.hasStmt(firstStmtNum, StmtType::ASSIGN)) {
    return result;
  }

  if (affectsCache.getIsComplete() &&
      affectsCache.getDirectSuccessorMap().count(firstStmtNum)) {
    auto stmtFilter = stmtStore.getStmtFilterPredicate(StmtType::ASSIGN);
    return CollectionUtils::intSetToStrVector(
        affectsCache.getDirectSuccessors(firstStmtNum), stmtFilter);
  }

  const std::string& v =
      *modifiesSStore.getDirectSuccessors(firstStmtNum).begin();

  findAffectsPairs(firstStmtNum, firstStmtNum, v, done, resultPairs);

  for (const auto& pair : resultPairs) {
    result.emplace_back(pair.second);
    affectsCache.addRelation(stoi(pair.first), stoi(pair.second));
  }

  return result;
}

std::vector<std::string> AffectsReader::getAffectedBy(int secondStmtNum,
                                                      StmtType stmtType) {
  std::vector<std::string> result;
  std::unordered_set<std::string> usedVariables;

  if (!stmtStore.hasStmt(secondStmtNum, StmtType::ASSIGN)) {
    return result;
  }

  if (affectsCache.getIsComplete() &&
      affectsCache.getDirectAncestorMap().count(secondStmtNum)) {
    auto stmtFilter = stmtStore.getStmtFilterPredicate(StmtType::ASSIGN);
    return CollectionUtils::intSetToStrVector(
        affectsCache.getDirectAncestors(secondStmtNum), stmtFilter);
  }

  if (usesSStore.hasDirectSuccessors(secondStmtNum)) {
    usedVariables = usesSStore.getDirectSuccessors(secondStmtNum);
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
      if (isAffects(stmt, secondStmtNum)) {
        result.emplace_back(std::to_string(stmt));
        affectsCache.addRelation(stmt, secondStmtNum);
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
  std::vector<std::pair<std::string, std::string>> result;

  const auto assignStmts = stmtStore.getAllStmtsOf(StmtType::ASSIGN);

  for (const auto& assign : assignStmts) {
    if (!modifiesSStore.hasDirectSuccessors(assign)) continue;
    std::unordered_set<std::string> done;
    std::string v = *modifiesSStore.getDirectSuccessors(assign).begin();

    findAffectsPairs(assign, assign, v, done, result);
    if (!result.empty()) {
      return true;
    }
  }

  return !result.empty();
}
