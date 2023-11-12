#pragma once

#include "pkb/interfaces/writers/INextWriter.h"
#include "pkb/storage/relation_storage/NextStore.h"

class NextWriter : INextWriter {
 private:
  NextStore& nextStore;

 protected:
  explicit NextWriter(NextStore& nextStore) : nextStore(nextStore) {}

 public:
  void addNext(int from, int to) override;
};
