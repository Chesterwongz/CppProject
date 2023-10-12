#include "PatternStorage.h"

void PatternStorage::setAssignPattern(const std::string& variableName,
                                      const std::string& rpn,
                                      int statementNumber) {
  variablePatternStorage[variableName].emplace_back(rpn, statementNumber);
  statementPatternStorage[statementNumber] = std::make_pair(rpn, variableName);
}

void PatternStorage::setWhilePattern(int statementNumber,
                                     const std::string& variableName) {
  whilePatternStorage[statementNumber].insert(variableName);
}

void PatternStorage::setIfPattern(int statementNumber,
                                  const std::string& variableName) {
  ifPatternStorage[statementNumber].insert(variableName);
}

std::vector<std::pair<std::string, std::string>>
PatternStorage::getAllAssignStatements() {
  std::vector<std::pair<std::string, std::string>> result;
  result.reserve(statementPatternStorage.size());
  for (const auto& entry : statementPatternStorage) {
    result.emplace_back(
        std::make_pair(std::to_string(entry.first), entry.second.second));
  }

  return result;
}

std::vector<std::pair<std::string, std::string>>
PatternStorage::getAllAssignStatementsWithVariable(
    const std::string& variableName) {
  std::vector<std::pair<std::string, std::string>> result;

  auto it = variablePatternStorage.find(variableName);
  if (it != variablePatternStorage.end()) {
    for (const auto& pair : it->second) {
      result.emplace_back(
          std::make_pair(std::to_string(pair.second), variableName));
    }
  }

  return result;
}

std::vector<std::pair<std::string, std::string>>
PatternStorage::getAssignPattern(const std::string& variableName,
                                 const std::string& rpn, bool isExact) {
  std::vector<std::pair<std::string, std::string>> result;

  auto processEntryWithWildcard = [&](const auto& entry) {
    if (isExact) {
      if (entry.second.first == rpn) {
        result.emplace_back(
            std::make_pair(std::to_string(entry.first), entry.second.second));
      }
    } else {
      if (entry.second.first.find(rpn) != std::string::npos) {
        result.emplace_back(
            std::make_pair(std::to_string(entry.first), entry.second.second));
      }
    }
  };

  auto processEntryWithoutWildcard = [&](const auto& entry) {
    if (isExact) {
      if (entry.second.first == rpn && entry.second.second == variableName) {
        result.emplace_back(
            std::make_pair(std::to_string(entry.first), variableName));
      }
    } else {
      if (entry.second.first.find(rpn) != std::string::npos &&
          entry.second.second == variableName) {
        result.emplace_back(
            std::make_pair(std::to_string(entry.first), variableName));
      }
    }
  };

  if ((variableName == WILDCARD_KEYWORD) && (rpn == WILDCARD_KEYWORD)) {
    result = getAllAssignStatements();
  } else if (variableName == WILDCARD_KEYWORD) {
    for (const auto& entry : statementPatternStorage) {
      processEntryWithWildcard(entry);
    }
  } else if (rpn == WILDCARD_KEYWORD) {
    result = getAllAssignStatementsWithVariable(variableName);
  } else {
    for (const auto& entry : statementPatternStorage) {
      processEntryWithoutWildcard(entry);
    }
  }

  return result;
}

std::vector<std::pair<std::string, std::string>>
PatternStorage::getExactAssignPattern(const std::string& variableName,
                                      const std::string& rpn) {
  return getAssignPattern(variableName, rpn, true);
}

std::vector<std::pair<std::string, std::string>>
PatternStorage::getPartialAssignPattern(const std::string& variableName,
                                        const std::string& rpn) {
  return getAssignPattern(variableName, rpn, false);
}

std::vector<std::pair<std::string, std::string>>
PatternStorage::getConditionPattern(
    const std::unordered_map<int, std::unordered_set<std::string>>& storage,
    const std::string& variableName) {
  std::vector<std::pair<std::string, std::string>> result;

  bool isWildcard = (variableName == WILDCARD_KEYWORD);

  for (const auto& entry : storage) {
    const std::string& stmtNum = std::to_string(entry.first);
    for (const std::string& var : entry.second) {
      if (isWildcard || var == variableName) {
        result.emplace_back(std::make_pair(stmtNum, var));
      }
    }
  }

  return result;
}

std::vector<std::pair<std::string, std::string>>
PatternStorage::getWhilePattern(const std::string& variableName) {
  return getConditionPattern(whilePatternStorage, variableName);
}

std::vector<std::pair<std::string, std::string>> PatternStorage::getIfPattern(
    const std::string& variableName) {
  return getConditionPattern(ifPatternStorage, variableName);
}
