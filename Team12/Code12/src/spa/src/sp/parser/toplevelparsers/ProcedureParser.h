#pragma once

#include "StmtLstParser.h"
#include "sp/ast/ProcNode.h"
#include "sp/constants/KeywordConstants.h"
#include "sp/parser/abstractparser/AbstractParser.h"

class ProcedureParser : public AbstractParser {
 public:
  explicit ProcedureParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)){};

  std::optional<std::unique_ptr<TNode>> parse() override;
};
