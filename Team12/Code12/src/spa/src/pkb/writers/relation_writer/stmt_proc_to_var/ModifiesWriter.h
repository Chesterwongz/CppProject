#pragma once

#include <string>

#include "pkb/interfaces/writers/IModifiesWriter.h"
#include "pkb/storage/ModifiesPStore.h"
#include "pkb/storage/ModifiesSStore.h"

class ModifiesWriter : public IModifiesWriter {
 private:
  ModifiesSStore& modifiesStore;
  ModifiesPStore& modifiesPStore;

 protected:
  ModifiesWriter(ModifiesSStore& modifiesStore, ModifiesPStore& modifiesPStore)
      : modifiesStore(modifiesStore), modifiesPStore(modifiesPStore) {}

 public:
  void addModifies(const std::string& varName, int stmtNum) override;
  void addModifies(const std::string& varName,
                   const std::string& procName) override;
};
