#pragma once

#include <string>

#include "pkb/storage/ModifiesPStore.h"
#include "pkb/storage/ModifiesStore.h"
#include "pkb/interfaces/writers/IModifiesWriter.h"

class ModifiesWriter : public IModifiesWriter {
 private:
  ModifiesStore& modifiesStore;
  ModifiesPStore& modifiesPStore;

 protected:
  ModifiesWriter(ModifiesStore& modifiesStore, ModifiesPStore& modifiesPStore)
      : modifiesStore(modifiesStore), modifiesPStore(modifiesPStore) {}

 public:
  void addModifies(const std::string& varName, int stmtNum) override;
  void addModifies(const std::string& varName,
                   const std::string& procName) override;
};
