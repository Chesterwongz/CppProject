#pragma once

#include "sp/parser/abstractparser/AbstractParser.h"
#include "sp/parser/exprparser/ExprParser.h"
#include "sp/parser/terminalparsers/ConstParser.h"
#include "sp/parser/terminalparsers/VarParser.h"

class FactorParser : public AbstractParser {
 public:
  explicit FactorParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)) {}

  std::optional<std::unique_ptr<TNode>> parse() override;
};
