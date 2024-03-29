#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/parser/condexprparser/CondExprParser.h"
#include "sp/parser/toplevelparsers/StmtLstParser.h"

class IfParser : public AbstractParser {
 public:
  explicit IfParser(ParserContext& context)
      : AbstractParser(context) {}
  std::optional<std::unique_ptr<TNode>> parse() override;
};
