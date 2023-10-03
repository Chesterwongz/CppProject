#pragma once

#include "sp/ast/statements/IfNode.h"
#include "sp/parser/abstractparser/AbstractParser.h"
#include "sp/parser/condexprparser/CondExprParser.h"
#include "sp/parser/toplevelparsers/StmtLstParser.h"

class IfParser : public AbstractParser {
 public:
  explicit IfParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)){};
  std::optional<std::unique_ptr<TNode>> parse() override;
};
