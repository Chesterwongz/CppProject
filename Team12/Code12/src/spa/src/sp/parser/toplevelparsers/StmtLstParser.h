#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/ast/StmtListNode.h"
#include "sp/parser/stmtparsers/StmtParser.h"

class StmtLstParser : public AbstractParser {
 public:
  explicit StmtLstParser(ParserContext& context)
      : AbstractParser(context) {}
  std::optional<std::unique_ptr<TNode>> parse() override;
};
