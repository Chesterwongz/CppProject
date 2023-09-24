#pragma once

#include "ArithmNode.h"
#include "sp/constants/OperatorConstants.h"

class TimesNode : public ArithmNode {
public:
    TimesNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right):
        ArithmNode(TNodeType::TNODE_TIMES, op::kTimes, std::move(left), std::move(right)) {}

};
