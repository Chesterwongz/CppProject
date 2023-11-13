#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/ast/terminals/ConstNode.h"

class ConstParser : public AbstractParser {
 public:
  explicit ConstParser(ParserContext& context)
      : AbstractParser(context) {}
  std::optional<std::unique_ptr<TNode>> parse() override;
};
