#pragma once

#include <string>

#include "pkb/interfaces/writers/IUsesWriter.h"
#include "pkb/storage/relation_storage/RelationStore.h"

class UsesWriter : public IUsesWriter {
 private:
  RelationStore<int, std::string>& usesStore;
  RelationStore<std::string, std::string>& usesPStore;

 protected:
  UsesWriter(RelationStore<int, std::string>& usesStore,
             RelationStore<std::string, std::string>& usesPStore)
      : usesStore(usesStore), usesPStore(usesPStore) {}

 public:
  void addUses(const std::string& varName, int stmtNum) override;
  void addUses(const std::string& varName,
               const std::string& procName) override;
};
