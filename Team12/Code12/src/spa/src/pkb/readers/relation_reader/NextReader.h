#pragma once

#include <string>
#include <unordered_set>

#include "pkb/interfaces/readers/INextReader.h"
#include "pkb/interfaces/storage/cfg_storage/ICfgStorage.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"

class NextReader : public INextReader {
 private:
  IEntityStorage& entityStorage;
  ICfgStorage& cfgStorage;

 public:
  explicit NextReader(ICfgStorage& cfgStorage, IEntityStorage& entityStorage)
      : cfgStorage(cfgStorage), entityStorage(entityStorage) {}

  std::vector<std::pair<std::string, std::string>> getNextPairs(
      StmtType firstStmtType, StmtType secondStmtType) override;

  bool isNext(int firstStmtNumber, int secondStmtNumber) override;

  std::vector<std::string> getNextFirstStmt(int secondStmtNumber,
                                            StmtType firstStmtType) override;

  std::vector<std::string> getNextSecondStmt(int firstStmtNumber,
                                             StmtType secondStmtType) override;

  std::vector<std::pair<std::string, std::string>> getNextStarPairs(
      StmtType firstStmtType, StmtType secondStmtType) override;

  bool isNextStar(int firstStmtNumber, int secondStmtNumber) override;

  std::vector<std::string> getNextStarFirstStmt(
      int secondStmtNumber, StmtType firstStmtType) override;

  std::vector<std::string> getNextStarSecondStmt(
      int firstStmtNumber, StmtType secondStmtType) override;
};
