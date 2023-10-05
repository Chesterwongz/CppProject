#pragma once

#include <memory>
#include <string>
#include <utility>

#include "AssignParser.h"
#include "sp/parser/abstractparser/AbstractParser.h"
#include "sp/parser/stmtparsers/factory/StmtParserFactory.h"

class StmtParser : public AbstractParser {
 public:
  explicit StmtParser(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)) {}

  std::optional<std::unique_ptr<TNode>> parse() override;
};
