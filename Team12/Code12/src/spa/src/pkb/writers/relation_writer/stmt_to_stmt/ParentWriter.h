#pragma once

#include "pkb/interfaces/writers/IParentWriter.h"
#include "pkb/storage/relation_storage/RelationTStore.h"

class ParentWriter : public IParentWriter {
 private:
  RelationTStore<int>& parentStore;

 protected:
  explicit ParentWriter(RelationTStore<int>& parentStore)
      : parentStore(parentStore) {}

 public:
  void addParent(int parent, int child) override;
  void setParentStarRelationship(int parent, int child) override;
};
