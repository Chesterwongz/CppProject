#pragma once

#include <memory>
#include <string>
#include <utility>

#include "RelExprParser.h"
#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/ast/expressions/conditional/NotNode.h"

class CondExprParser : public AbstractParser {
 public:
  explicit CondExprParser(ParserContext& context)
      : AbstractParser(context) {}
  std::optional<std::unique_ptr<TNode>> parse() override;
};
