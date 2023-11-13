#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/parser/condexprparser/RelFactorParser.h"

class RelExprParser : public AbstractParser {
 public:
  explicit RelExprParser(ParserContext& context)
      : AbstractParser(context) {}
  std::optional<std::unique_ptr<TNode>> parse() override;
};
