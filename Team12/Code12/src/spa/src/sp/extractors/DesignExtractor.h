#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#include "Extractor.h"
#include "Populator.h"
#include "common/ast/TNode.h"
#include "pkb/facade/PKBWriter.h"
#include "sp/extractors/calls/CallsExtractor.h"
#include "sp/extractors/cfg/CFGExtractor.h"
#include "sp/extractors/entity/EntityExtractor.h"
#include "sp/extractors/follows/FollowsExtractor.h"
#include "sp/extractors/modifies/ModifiesExtractor.h"
#include "sp/extractors/parent/ParentExtractor.h"
#include "sp/extractors/pattern/PatternExtractor.h"
#include "sp/extractors/uses/UsesExtractor.h"

class DesignExtractor {
 private:
  std::vector<std::unique_ptr<Extractor>> extractors;
  Populator populator;

 public:
  explicit DesignExtractor(PKBWriter& pkbWriter);
  void extract(TNode& node);
};
