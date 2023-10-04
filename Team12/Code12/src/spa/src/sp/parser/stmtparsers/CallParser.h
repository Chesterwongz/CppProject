#pragma once

#include <memory>
#include <string>
#include <utility>

#include "sp/ast/statements/CallNode.h"
#include "sp/parser/abstractparser/AbstractParser.h"

class CallParser : public AbstractParser {
 public:
  explicit CallParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)) {}
  std::optional<std::unique_ptr<TNode>> parse() override;
};
