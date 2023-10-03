#pragma once

#include "ProcedureParser.h"
#include "sp/ast/ProgramNode.h"
#include "sp/parser/abstractparser/AbstractParser.h"

class ProgramParser : public AbstractParser {
 public:
  explicit ProgramParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)){};

  std::optional<std::unique_ptr<TNode>> parse() override;
};
