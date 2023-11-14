#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <utility>

#include "common/ast/TNode.h"
#include "common/parser/IParser.h"
#include "common/parser/parsercontext/ParserContext.h"
#include "sp/exceptions/SpSyntaxError.h"

class AbstractParser : public IParser {
 protected:
  ParserContext& context;

  explicit AbstractParser(ParserContext& context)
      : context(context) {}

  std::function<void(const std::optional<std::unique_ptr<TNode>> &)>
  requireTNodeOpt(TNodeType nodeType);

 public:
  std::optional<unique_ptr<TNode>> parseWithBrackets();
};
