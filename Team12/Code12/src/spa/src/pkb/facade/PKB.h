#pragma once

#include "PKBReader.h"
#include "PKBStorage.h"
#include "PKBWriter.h"
#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"

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
