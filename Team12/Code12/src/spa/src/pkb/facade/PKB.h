#pragma once

#include "PKBReader.h"
#include "PKBStorage.h"
#include "PKBStore.h"
#include "PKBWriter.h"

class PKB {
 private:
  PKBStorage storage;
  PKBStore store;
  PKBReader reader;
  PKBWriter writer;

 public:
  PKB() : storage(), writer(storage), reader(storage, store) {}
  PKBWriter& getWriter() { return writer; }
  PKBReader& getReader() { return reader; }
};
