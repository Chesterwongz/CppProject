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
#include "pkb/readers/entity_reader/DesignEntitiesReader.h"
#include "pkb/readers/relation_reader/stmt_proc_to_var/ModifiesReader.h"
#include "pkb/readers/relation_reader/stmt_proc_to_var/UsesReader.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/NextReader.h"
#include "pkb/storage/entity_storage/StmtStorage.h"
#include "pkb/storage/relation_storage/proc_to_proc/CallsStorage.h"
#include "pkb/storage/relation_storage/stmt_proc_to_var/ModifiesStorage.h"
#include "pkb/storage/relation_storage/stmt_proc_to_var/UsesStorage.h"
#include "pkb/storage/relation_storage/stmt_to_stmt/NextStorage.h"
#include "pkb/storage/ModifiesStore.h"
#include "pkb/storage/StmtStore.h"
#include "pkb/storage/CallsStore.h"
#include "pkb/storage/NextStore.h"
#include "pkb/storage/UsesStore.h"
// try storage and not reader or store

class AffectsReader : public IAffectsReader {
 private:
  CallsStorage& calls_storage_;
  ModifiesStorage& modifies_storage_;
  NextStorage& next_storage_;
  StmtStorage& stmt_storage_;
  UsesStorage& uses_storage_;

 public:
  explicit AffectsReader(CallsStorage& callsStorage,
                         ModifiesStorage& modifiesStorage,
                         NextStorage& nextStorage, StmtStorage& stmtStorage,
                         UsesStorage& usesStorage)
      : calls_storage_(callsStorage),
        modifies_storage_(modifiesStorage),
        next_storage_(nextStorage),
        stmt_storage_(stmtStorage),
        uses_storage_(usesStorage) {}

  std::vector<std::pair<std::string, std::string>> getAffectsPairs();

  bool isAffects(int firstStmtNum, int secondStmtNum);

  std::vector<std::string> getAffects(int firstStmtNum);
  std::vector<std::string> getAffectedBy(int secondStmtNum);

  void FindAffectsPairs(
      int originalStatement, int currentStatement, const std::string& variable,
      unordered_set<std::string>& done,
      std::vector<std::pair<std::string, std::string>>& result);
};