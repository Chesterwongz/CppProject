#include "AffectsReader.h"

std::vector<std::pair<std::string, std::string>>
AffectsReader::getAffectsPairs() {
  if (affectsCache.getIsComplete()) {
    auto stmtFilters = stmtStore.getStmtStmtFilterPredicates(StmtType::ASSIGN,
                                                             StmtType::ASSIGN);
    return CollectionUtils::intIntMapSetToStrPairVector(
        affectsCache.getDirectRelations(), stmtFilters);
  }

  std::vector<std::pair<std::string, std::string>> result;

  const auto assignStmts = stmtStore.getAllStmtsOf(StmtType::ASSIGN);

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

  // (REMOVE LATER) if the relation exists in cache, return true
  if (affectsCache.hasDirectRelation(firstStmtNum, secondStmtNum)) {
    return affectsCache.hasDirectRelation(firstStmtNum, secondStmtNum);
  }

  // (REMOVE LATER) if cache is completed and relation doesnt exist, return
  // false
  if (affectsCache.getIsComplete() &&
      !affectsCache.hasDirectRelation(firstStmtNum, secondStmtNum)) {
    return affectsCache.hasDirectRelation(firstStmtNum, secondStmtNum);
  }

  // (REMOVE LATER) if relation doesnt exist, and cache is not complete, manual
  // check

  std::vector<std::vector<int>> paths =
      pathsFromTo(firstStmtNum, secondStmtNum);

  std::unordered_set<std::string> usedVariables =
      usesSStore.getDirectSuccessors(secondStmtNum);

  if (!paths.empty()) {
    std::unordered_set<std::string> modifiedVars =
        modifiesSStore.getDirectSuccessors(firstStmtNum);

    for (const std::string& var : usedVariables) {
      if (!modifiedVars.count(var)) {
        continue;
      }
      bool isChanged = true;

      for (const std::vector<int>& path : paths) {
        bool isValidType = false;
        bool isVarModified = false;

        for (int stmt : path) {
          if (modifiesSStore.hasDirectSuccessors(stmt)) {
            isValidType = isCallReadAssign(stmt);
            if (modifiesSStore.getDirectSuccessors(stmt).count(var) &&
                isValidType) {
              isVarModified = true;
              break;
            }
          }
        }

        if (!isVarModified) {
          isChanged = false;
          break;
        }
      }

      if (!isChanged) {
        affectsCache.addRelation(firstStmtNum, secondStmtNum);
        return true;
      }
    }

    return false;
  } else {
    return (nextStore.hasDirectRelation(firstStmtNum, secondStmtNum) &&
            stmtStore.hasStmt(firstStmtNum, StmtType::ASSIGN) &&
            stmtStore.hasStmt(secondStmtNum, StmtType::ASSIGN) &&
            usedVariables.count(
                *modifiesSStore.getDirectSuccessors(firstStmtNum).begin()));
  }
}

std::vector<std::vector<int>> AffectsReader::pathsFromTo(int start,
                                                         int target) {
  std::vector<std::vector<int>> paths;
  std::vector<int> currentPath;
  std::unordered_set<int> visited;

  std::unordered_set<int> successors = nextStore.getDirectSuccessors(start);
  for (int successor : successors) {
    dfs(successor, target, currentPath, paths, visited);
  }

  return paths;
}

void AffectsReader::dfs(int current, int target, std::vector<int>& currentPath,
                        std::vector<std::vector<int>>& paths,
                        std::unordered_set<int>& visited) {
  visited.insert(current);
  currentPath.push_back(current);

  if (current == target) {
    paths.push_back(
        std::vector<int>(currentPath.begin(), currentPath.end() - 1));
  } else {
    if (nextStore.hasDirectSuccessors(current)) {
      std::unordered_set<int> successors =
          nextStore.getDirectSuccessors(current);
      for (int successor : successors) {
        if (visited.find(successor) == visited.end()) {
          dfs(successor, target, currentPath, paths, visited);
        }
      }
    }
  }

  visited.erase(current);
  currentPath.pop_back();
}

std::vector<std::string> AffectsReader::getAffects(int firstStmtNum,
                                                   StmtType stmtType) {
  std::vector<std::string> result;
  std::vector<std::pair<std::string, std::string>> resultPairs;
  std::unordered_set<std::string> done;

  if (!stmtStore.hasStmt(firstStmtNum, StmtType::ASSIGN)) {
    return result;
  }

  // (REMOVE LATER) if cache is not empty, and stmtNum exists in map, return its
  // successors
  if (!affectsCache.getDirectRelations().empty() &&
      affectsCache.getDirectRelations().find(firstStmtNum) !=
          affectsCache.getDirectRelations().end()) {
    auto stmtFilter = stmtStore.getStmtFilterPredicate(StmtType::ASSIGN);
    return CollectionUtils::intSetToStrVector(
        affectsCache.getDirectSuccessors(firstStmtNum), stmtFilter);
  }

  std::string v = *modifiesSStore.getDirectSuccessors(firstStmtNum).begin();

  findAffectsPairs(firstStmtNum, firstStmtNum, v, done, resultPairs);

  for (auto pair : resultPairs) {
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

  // (REMOVE LATER) if cache is not empty, and stmtNum exists in map
  if (!affectsCache.getDirectRelations().empty() &&
      affectsCache.getDirectBackwardRelations().find(secondStmtNum) !=
          affectsCache.getDirectBackwardRelations().end()) {
    auto stmtFilter = stmtStore.getStmtFilterPredicate(StmtType::ASSIGN);
    return CollectionUtils::intSetToStrVector(
        affectsCache.getDirectAncestors(secondStmtNum), stmtFilter);
  }

  if (usesSStore.hasDirectSuccessors(secondStmtNum)) {
    usedVariables = usesSStore.getDirectSuccessors(secondStmtNum);
    std::unordered_set<int> allModifyingStmts;
    for (std::string var : usedVariables) {
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