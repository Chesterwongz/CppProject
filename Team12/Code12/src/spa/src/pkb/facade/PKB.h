#pragma once

#include "PKBReader.h"
#include "PKBStore.h"
#include "PKBWriter.h"

class PKB {
 private:
  PKBStore store;
  PKBReader reader;
  PKBWriter writer;

 public:
  PKB() : store(), writer(store), reader(store) {}
  PKBWriter& getWriter() { return writer; }
  PKBReader& getReader() { return reader; }
};
