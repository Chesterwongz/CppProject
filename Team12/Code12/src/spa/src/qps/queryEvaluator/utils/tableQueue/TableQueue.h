#pragma once

#include <algorithm>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/clause/Clause.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/query/Query.h"

using std::vector, std::unique_ptr, std::string;

class TableQueue {
 private:
  std::priority_queue<IntermediateTable> tableQueue;

 public:
  void addTable(IntermediateTable table);

  IntermediateTable getJoinResult();
};


/**
 * for min heap implementation
 */
bool operator<(const IntermediateTable &thisTable,
               const IntermediateTable &otherTable);

