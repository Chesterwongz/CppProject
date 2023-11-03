#pragma once

#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/Constants.h"
#include "common/utils/CollectionUtils.h"
#include "pkb/interfaces/readers/IAffectsReader.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/relation_storage/ModifiesSStore.h"
#include "pkb/storage/relation_storage/NextStore.h"
#include "pkb/storage/relation_storage/UsesSStore.h"

class AffectsReader : public IAffectsReader {
 private:
  ModifiesSStore& modifiesSStore;
  NextStore& nextStore;
  StmtStore& stmtStore;
  UsesSStore& usesSStore;

 public:
  explicit AffectsReader(ModifiesSStore& modifiesSStore, NextStore& nextStore,
                         StmtStore& stmtStore, UsesSStore& usesSStore)
      : modifiesSStore(modifiesSStore),
        nextStore(nextStore),
        stmtStore(stmtStore),
        usesSStore(usesSStore) {}

  std::vector<std::pair<std::string, std::string>> getAffectsPairs() override;

  bool isAffects(int firstStmtNum, int secondStmtNum) override;

  std::vector<std::string> getAffects(int firstStmtNum,
                                      StmtType stmtType) override;
  std::vector<std::string> getAffectedBy(int secondStmtNum,
                                         StmtType stmtType) override;

  void findAffectsPairs(
      int originalStmt, int currentStmt, const std::string& variable,
      std::unordered_set<std::string>& done,
      std::vector<std::pair<std::string, std::string>>& result);
};
