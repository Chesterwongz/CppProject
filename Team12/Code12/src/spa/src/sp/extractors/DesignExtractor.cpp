#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(PKBWriter& pkbWriter) : pkbWriter(pkbWriter) {
  extractors.emplace_back(std::make_unique<CallsExtractor>(pkbWriter));
  extractors.emplace_back(std::make_unique<FollowsExtractor>(pkbWriter));
  extractors.emplace_back(std::make_unique<ParentExtractor>(pkbWriter));
  extractors.emplace_back(std::make_unique<UsesExtractor>(pkbWriter));
  extractors.emplace_back(std::make_unique<ModifiesExtractor>(pkbWriter));
  extractors.emplace_back(std::make_unique<EntityExtractor>(pkbWriter));
  extractors.emplace_back(std::make_unique<PatternExtractor>(pkbWriter));
  extractors.emplace_back(std::make_unique<NextExtractor>(pkbWriter));
}

void DesignExtractor::extract(TNode& node) {
  populator.populate(node, extractors);
  pkbWriter.computeAllRelationsT();
}
