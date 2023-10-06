#pragma once

#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <string>

#include "Extractor.h"
#include "sp/ast/TNode.h"
#include "sp/extractors/calls/CallsExtractor.h"
#include "sp/extractors/follows/FollowsExtractor.h"
#include "sp/extractors/parent/ParentExtractor.h"
#include "sp/extractors/uses/UsesExtractor.h"
#include "sp/extractors/modifies/ModifiesExtractor.h"
#include "sp/extractors/entity/EntityExtractor.h"
#include "sp/extractors/pattern/PatternExtractor.h"
#include "sp/extractors/cfg/CFGExtractor.h"
#include "pkb/facade/PKBWriter.h"
#include "Populator.h"

class DesignExtractor {
 private:
  std::vector<std::unique_ptr<Extractor>> extractors;
  Populator populator;
  PKBWriter& pkbWriter;

 public:
  explicit DesignExtractor(PKBWriter& pkbWriter);
  void extract(TNode& node);
};
