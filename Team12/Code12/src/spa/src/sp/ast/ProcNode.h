#pragma once

#include <utility>

#include "TNode.h"
#include "StmtListNode.h"

class ProcNode : public TNode {
public:
    explicit ProcNode(std::string name): TNode(TNodeType::TNODE_PROCEDURE, std::move(name)) {}
    void accept(Extractor& e) const override;
    void cleanup(Extractor& e) const override;
    [[nodiscard]] int getProcStart() const;
};
