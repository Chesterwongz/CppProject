#pragma once

#include <string>

#include "pkb/interfaces/writers/IModifiesWriter.h"
#include "pkb/storage/relation_storage/RelationStore.h"

class ModifiesWriter : public IModifiesWriter {
 private:
  RelationStore<int, std::string>& modifiesStore;
  RelationStore<std::string, std::string>& modifiesPStore;

 protected:
  ModifiesWriter(RelationStore<int, std::string>& modifiesStore,
                 RelationStore<std::string, std::string>& modifiesPStore)
      : modifiesStore(modifiesStore), modifiesPStore(modifiesPStore) {}

 public:
  void addModifies(const std::string& varName, int stmtNum) override;
  void addModifies(const std::string& varName,
                   const std::string& procName) override;
};
