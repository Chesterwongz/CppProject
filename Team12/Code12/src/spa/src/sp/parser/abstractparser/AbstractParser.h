#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <utility>
#include "sp/parser/IParser.h"
#include "sp/parser/parsercontext/ParserContext.h"
#include "sp/ast/TNode.h"

class AbstractParser : public IParser {
protected:
    std::shared_ptr<ParserContext> context;

    std::function<void(const std::optional<std::unique_ptr<TNode>> &)> requireTNodeOpt(TNodeType nodeType);

    explicit AbstractParser(std::shared_ptr<ParserContext> context) : context(std::move(context)) {}

};
