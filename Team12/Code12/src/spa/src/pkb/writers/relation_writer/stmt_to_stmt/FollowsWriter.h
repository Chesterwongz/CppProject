#pragma once

#include "pkb/interfaces/writers/IFollowsWriter.h"
#include "pkb/storage/FollowsStore.h"

class FollowsWriter : public IFollowsWriter {
 private:
  FollowsStore& followsStore;

 protected:
  explicit FollowsWriter(FollowsStore& followsStore)
      : followsStore(followsStore) {}

 public:
  void addFollows(int from, int to) override;
};
