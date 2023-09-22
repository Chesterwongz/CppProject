#include "Populator.h"

Populator::Populator() = default;

void Populator::populate(TNode *node, const std::vector<std::unique_ptr<Extractor>> &extractorVector) {
    for (const auto &extractor : extractorVector) {
        node->accept(extractor.get());
    }
    for (auto child : node->getChildren()) {
        populate(child, extractorVector);
    }
    for (const auto &extractor : extractorVector) {
        node->cleanup(extractor.get());
    }
}

