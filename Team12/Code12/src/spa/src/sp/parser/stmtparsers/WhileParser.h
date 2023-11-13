#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/parser/condexprparser/CondExprParser.h"
#include "sp/parser/toplevelparsers/StmtLstParser.h"

class WhileParser : public AbstractParser {
 public:
  explicit WhileParser(ParserContext& context)
      : AbstractParser(context) {}
  std::optional<std::unique_ptr<TNode>> parse() override;
};
