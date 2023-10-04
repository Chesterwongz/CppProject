#pragma once

#include <memory>
#include <utility>

#include "sp/ast/statements/WhileNode.h"
#include "sp/parser/abstractparser/AbstractParser.h"
#include "sp/parser/condexprparser/CondExprParser.h"
#include "sp/parser/toplevelparsers/StmtLstParser.h"

class WhileParser : public AbstractParser {
 public:
  explicit WhileParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)) {}
  std::optional<std::unique_ptr<TNode>> parse() override;
};
