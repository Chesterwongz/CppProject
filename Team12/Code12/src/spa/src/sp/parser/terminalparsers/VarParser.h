#pragma once

#include "sp/ast/terminals/VarNode.h"
#include "sp/parser/abstractparser/AbstractParser.h"

class VarParser : public AbstractParser {
 public:
  explicit VarParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)){};
  std::optional<std::unique_ptr<TNode>> parse() override;
};
