#pragma once

#include "pkb/interfaces/writers/IFollowsWriter.h"
#include "pkb/storage/relation_storage/RelationTStore.h"

class FollowsWriter : public IFollowsWriter {
 private:
  RelationTStore<int>& followsStore;

 protected:
  explicit FollowsWriter(RelationTStore<int>& followsStore)
      : followsStore(followsStore) {}

 public:
  void addFollows(int from, int to) override;
};
