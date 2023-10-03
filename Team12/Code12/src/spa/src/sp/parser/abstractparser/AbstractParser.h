#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <utility>

#include "sp/ast/TNode.h"
#include "sp/parser/IParser.h"
#include "sp/parser/parsercontext/ParserContext.h"

class AbstractParser : public IParser {
 protected:
  std::shared_ptr<ParserContext> context;

  explicit AbstractParser(std::shared_ptr<ParserContext> context)
      : context(std::move(context)) {}

  std::function<void(const std::optional<std::unique_ptr<TNode>> &)>
  requireTNodeOpt(TNodeType nodeType);

 public:
  std::optional<unique_ptr<TNode>> parseWithBrackets();
};
