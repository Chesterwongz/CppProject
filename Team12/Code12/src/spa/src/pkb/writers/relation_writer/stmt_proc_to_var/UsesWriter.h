#pragma once

#include <string>

#include "pkb/interfaces/writers/IUsesWriter.h"
#include "pkb/storage/relation_storage/UsesPStore.h"
#include "pkb/storage/relation_storage/UsesSStore.h"

class UsesWriter : public IUsesWriter {
 private:
  UsesSStore& usesStore;
  UsesPStore& usesPStore;

 protected:
  UsesWriter(UsesSStore& usesStore, UsesPStore& usesPStore)
      : usesStore(usesStore), usesPStore(usesPStore) {}

 public:
  void addUses(const std::string& varName, int stmtNum) override;
  void addUses(const std::string& varName,
               const std::string& procName) override;
};
