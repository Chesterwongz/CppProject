#pragma once

#include <memory>
#include <string>
#include <utility>

#include "RelExprParser.h"
#include "sp/ast/expressions/conditional/NotNode.h"
#include "common/parser/abstractparser/AbstractParser.h"

class CondExprParser : public AbstractParser {
 public:
  explicit CondExprParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)) {}
  std::optional<std::unique_ptr<TNode>> parse() override;
};
