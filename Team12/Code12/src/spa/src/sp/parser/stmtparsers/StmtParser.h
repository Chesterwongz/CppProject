#pragma once

#include <memory>
#include <string>
#include <utility>

#include "AssignParser.h"
#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/parser/stmtparsers/factory/StmtParserFactory.h"

class StmtParser : public AbstractParser {
 public:
  explicit StmtParser(ParserContext& context)
      : AbstractParser(context) {}

  std::optional<std::unique_ptr<TNode>> parse() override;
};
