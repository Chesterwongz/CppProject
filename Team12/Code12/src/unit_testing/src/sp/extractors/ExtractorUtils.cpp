#include "ExtractorUtils.h"

unique_ptr<Extractor> getExtractor(MockPKBWriter &mockPKBWriter,
                                   AbstractionType abstractionType) {
  switch (abstractionType) {
    case AbstractionType::ENTITY:
      return make_unique<EntityExtractor>(mockPKBWriter);

    case AbstractionType::FOLLOWS:
      return make_unique<FollowsExtractor>(mockPKBWriter);

    case AbstractionType::MODIFIES:
      return make_unique<ModifiesExtractor>(mockPKBWriter);

    case AbstractionType::USES:
      return make_unique<UsesExtractor>(mockPKBWriter);

    case AbstractionType::PARENT:
      return make_unique<ParentExtractor>(mockPKBWriter);

    case AbstractionType::PATTERN:
      return make_unique<PatternExtractor>(mockPKBWriter);

    case AbstractionType::CALLS:
      return make_unique<CallsExtractor>(mockPKBWriter);

    case AbstractionType::CFG:
      return make_unique<CFGExtractor>(mockPKBWriter);

    default:
      throw SpException("Unknown abstraction type");
  }
}

void extractAbstraction(TNode &node, MockPKBWriter &mockPKBWriter,
                        AbstractionType abstractionType) {
  Populator populator;
  vector<unique_ptr<Extractor>> extractors;
  extractors.emplace_back(getExtractor(mockPKBWriter, abstractionType));
  populator.populate(node, extractors);
}

void extractAbstraction(const string &input, MockPKBWriter &mockPKBWriter,
                        AbstractionType abstractionType) {
  std::optional<std::unique_ptr<TNode>> nodeOpt =
      ProgramParser(std::move(std::make_shared<ParserContext>(input))).parse();
  if (!nodeOpt.has_value()) {
    throw SpParsingFailedException();
  }
  extractAbstraction(*nodeOpt.value(), mockPKBWriter, abstractionType);
}
