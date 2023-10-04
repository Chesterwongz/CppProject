#pragma once

#include <memory>

#include "sp/ast/statements/ReadNode.h"
#include "sp/parser/stmtparsers/templates/ReadPrintParserTemplate.h"

class ReadParser : public ReadPrintParserTemplate {
 public:
  explicit ReadParser(std::shared_ptr<ParserContext> context)
      : ReadPrintParserTemplate(std::move(context)) {}
  [[nodiscard]] std::unique_ptr<TNode> makeTNode() const override;
};
