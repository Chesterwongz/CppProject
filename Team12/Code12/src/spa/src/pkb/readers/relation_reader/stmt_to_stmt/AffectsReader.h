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
#include "pkb/storage/CallsStore.h"
#include "pkb/storage/ModifiesPStore.h"
#include "pkb/storage/ModifiesSStore.h"
#include "pkb/storage/NextStore.h"
#include "pkb/storage/StmtStore.h"
#include "pkb/storage/UsesSStore.h"

class AffectsReader : public IAffectsReader {
 private:
  CallsStore& callsStore;
  ModifiesPStore& modifiesPStore;
  ModifiesSStore& modifiesSStore;
  NextStore& nextStore;
  StmtStore& stmtStore;
  UsesSStore& usesSStore;

 public:
  explicit AffectsReader(CallsStore& callsStore, ModifiesPStore& modifiesPStore,
                         ModifiesSStore& modifiesSStore, NextStore& nextStore,
                         StmtStore& stmtStore, UsesSStore& usesSStore)
      : callsStore(callsStore),
        modifiesPStore(modifiesPStore),
        modifiesSStore(modifiesSStore),
        nextStore(nextStore),
        stmtStore(stmtStore),
        usesSStore(usesSStore) {}

  std::vector<std::pair<std::string, std::string>> getAffectsPairs();

  bool isAffects(int firstStmtNum, int secondStmtNum);

  std::vector<std::string> getAffects(int firstStmtNum);
  std::vector<std::string> getAffectedBy(int secondStmtNum);

  void FindAffectsPairs(
      int originalStmt, int currentStmt, const std::string& variable,
      std::unordered_set<std::string>& done,
      std::vector<std::pair<std::string, std::string>>& result);
};