#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/intermediateTable/IntermediateTable.h"

class IClause {
 public:
  virtual IntermediateTable evaluate(PKBReader& pkbReader) = 0;
  virtual bool isEquals(const IClause& other) = 0;
  virtual set<string> getClauseSynonyms() = 0;
  virtual string getKey() = 0;
  virtual ~IClause() = default;
};
