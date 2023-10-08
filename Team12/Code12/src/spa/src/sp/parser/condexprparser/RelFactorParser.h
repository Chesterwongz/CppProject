#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/parser/exprparser/ExprParser.h"
#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/parser/terminalparsers/ConstParser.h"
#include "sp/parser/terminalparsers/VarParser.h"

class RelFactorParser : public AbstractParser {
 public:
  explicit RelFactorParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)) {}
  std::optional<std::unique_ptr<TNode>> parse() override;
};
