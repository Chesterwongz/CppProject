#pragma once

#include "pkb/storage/FollowsStore.h"
#include "pkb/interfaces/writers/IFollowsWriter.h"

class FollowsWriter : public IFollowsWriter {
 private:
  FollowsStore& followsStore;

 protected:
  explicit FollowsWriter(FollowsStore& followsStore)
      : followsStore(followsStore) {}

 public:
  void addFollows(int from, int to) override;
};
