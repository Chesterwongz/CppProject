#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/Constants.h"
#include "pkb/interfaces/readers/INextReader.h"
#include "pkb/interfaces/storage/cfg_storage/ICfgStorage.h"
#include "pkb/interfaces/storage/entity_storage/IEntityStorage.h"
#include "pkb/interfaces/storage/entity_storage/IStmtStorage.h"

using GetStmtsFunction =
    std::unordered_set<int> (ICfgStorage::*)(const std::string&, int);

class NextReader : public INextReader {
 private:
  ICfgStorage& cfgStorage;
  IEntityStorage& entityStorage;
  IStmtStorage& stmtStorage;
  std::vector<std::string> getStmtsFrom(GetStmtsFunction getStmtsFunc,
                                        int stmtNum, StmtType type);

 public:
  NextReader(ICfgStorage& cfgStorage, IEntityStorage& entityStorage,
             IStmtStorage& stmtStorage)
      : cfgStorage(cfgStorage),
        entityStorage(entityStorage),
        stmtStorage(stmtStorage) {}

  std::vector<std::pair<std::string, std::string>> getNextPairs(
      StmtType firstStmtType, StmtType secondStmtType) override;

  bool isNext(int firstStmtNumber, int secondStmtNumber) override;

  std::vector<std::string> getPrevStmtsFrom(int secondStmtNumber,
                                            StmtType firstStmtType) override;

  std::vector<std::string> getNextStmtsFrom(int firstStmtNumber,
                                            StmtType secondStmtType) override;

  std::vector<std::pair<std::string, std::string>> getNextStarPairs(
      StmtType firstStmtType, StmtType secondStmtType) override;

  bool isNextStar(int firstStmtNumber, int secondStmtNumber) override;

  std::vector<std::string> getNextStarFirstStmt(
      int secondStmtNumber, StmtType firstStmtType) override;

  std::vector<std::string> getNextStarSecondStmt(
      int firstStmtNumber, StmtType secondStmtType) override;
};
