#pragma once

#include "pkb/interfaces/writers/IParentWriter.h"
#include "pkb/storage/ParentStore.h"

class ParentWriter : public IParentWriter {
 private:
  ParentStore& parentStore;

 protected:
  explicit ParentWriter(ParentStore& parentStore) : parentStore(parentStore) {}

 public:
  void addParent(int parent, int child) override;
  void setParentStarRelationship(int parent, int child) override;
};
