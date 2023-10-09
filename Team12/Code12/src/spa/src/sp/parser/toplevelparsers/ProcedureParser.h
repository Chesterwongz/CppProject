#pragma once

#include <memory>
#include <string>
#include <utility>

#include "StmtLstParser.h"
#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/ast/ProcNode.h"
#include "sp/constants/KeywordConstants.h"

class ProcedureParser : public AbstractParser {
 public:
  explicit ProcedureParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)) {}

  std::optional<std::unique_ptr<TNode>> parse() override;
};
