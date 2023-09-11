#pragma once

#include <memory>
#include "sp/ast/TNode.h"

class IParser {
public:
    virtual ~IParser() = default;
    virtual std::unique_ptr<TNode> parse() = 0;
};