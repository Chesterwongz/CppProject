#pragma once

#include <string>

#include "pkb/storage/UsesStore.h"
#include "pkb/storage/UsesPStore.h"
#include "pkb/interfaces/writers/IUsesWriter.h"

class UsesWriter : public IUsesWriter {
 private:
  UsesStore& usesStore;
  UsesPStore& usesPStore;

 protected:
  UsesWriter(UsesStore& usesStore, UsesPStore& usesPStore)
      : usesStore(usesStore), usesPStore(usesPStore) {}

 public:
  void addUses(const std::string& varName, int stmtNum) override;
  void addUses(const std::string& varName,
               const std::string& procName) override;
};
