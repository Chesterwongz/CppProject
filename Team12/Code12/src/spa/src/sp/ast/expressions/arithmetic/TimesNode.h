#pragma once

#include "ArithmNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class TimesNode : public ArithmNode {
public:
    TimesNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        ArithmNode(TNodeType::TNODE_TIMES, kTimes, std::move(left), std::move(right)) {}

};
