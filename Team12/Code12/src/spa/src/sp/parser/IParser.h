#pragma once

#include <memory>
#include <optional>
#include "sp/ast/TNode.h"

class IParser {
public:
    virtual ~IParser() = default;

    virtual std::optional<std::unique_ptr<TNode>> parse() = 0;
};