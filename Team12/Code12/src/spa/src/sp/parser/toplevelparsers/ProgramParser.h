#pragma once

#include <memory>
#include <string>
#include <utility>

#include "ProcedureParser.h"
#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/ast/ProgramNode.h"

class ProgramParser : public AbstractParser {
 public:
  explicit ProgramParser(ParserContext& context)
      : AbstractParser(context) {}

  std::optional<std::unique_ptr<TNode>> parse() override;
};
