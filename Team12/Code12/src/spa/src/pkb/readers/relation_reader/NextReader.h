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
#include "pkb/interfaces/storage/relation_storage/INextStorage.h"

using GetStmtsFunction =
    std::unordered_set<int> (INextStorage::*)(int);

class NextReader : public INextReader {
 private:
  INextStorage& nextStorage;
  IEntityStorage& entityStorage;
  IStmtStorage& stmtStorage;
  std::vector<std::string> getStmtsFrom(GetStmtsFunction getStmtsFunc,
                                        int stmtNum, StmtType type);

 public:
  NextReader(INextStorage& nextStorage, IEntityStorage& entityStorage,
             IStmtStorage& stmtStorage)
      : nextStorage(nextStorage),
        entityStorage(entityStorage),
        stmtStorage(stmtStorage) {}

  std::vector<std::pair<std::string, std::string>> getNextPairs(
      StmtType firstStmtType, StmtType secondStmtType) override;
  std::vector<std::pair<std::string, std::string>> getNextTPairs(
      StmtType firstStmtType, StmtType secondStmtType) override;

  bool isNext(int firstStmtNum, int secondStmtNum) override;
  bool isNextT(int firstStmtNum, int secondStmtNum) override;

  std::vector<std::string> getPrevStmts(int secondStmtNum,
                                        StmtType firstStmtType) override;
  std::vector<std::string> getPrevTStmts(int secondStmtNum,
                                         StmtType firstStmtType) override;

  std::vector<std::string> getNextStmts(int firstStmtNum,
                                        StmtType secondStmtType) override;
  std::vector<std::string> getNextTStmts(int firstStmtNum,
                                         StmtType secondStmtType) override;
};
