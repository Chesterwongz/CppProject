#pragma once

#include <memory>
#include <string>
#include <utility>

#include "sp/ast/terminals/ConstNode.h"
#include "common/parser/abstractparser/AbstractParser.h"

class ConstParser : public AbstractParser {
 public:
  explicit ConstParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)) {}
  std::optional<std::unique_ptr<TNode>> parse() override;
};
