#include "ExprNode.h"

ExprNode::ExprNode(TNodeType nodeType, std::string value, std::unique_ptr<ExprNode> left,
                   std::unique_ptr<ExprNode> right) : TNode(nodeType, std::move(value)) {
    addChild(std::move(left));
    if (right != nullptr) {
        addChild(std::move(right));
    }
}

void ExprNode::accept(Extractor *e) const {
    e->visitExpr(this);
}