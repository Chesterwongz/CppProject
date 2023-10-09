#pragma once

#include "PKBReader.h"
#include "PKBStorage.h"
#include "PKBWriter.h"

class PKB {
 private:
  PKBStorage storage;
  PKBReader reader;
  PKBWriter writer;

 public:
  PKB() : storage(), writer(storage), reader(storage) {}
  PKBWriter& getWriter() { return writer; }
  PKBReader& getReader() { return reader; }
};
