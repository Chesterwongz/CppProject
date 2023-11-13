#pragma once

#include <memory>
#include <string>
#include <utility>

#include "sp/ast/statements/ReadNode.h"
#include "sp/parser/stmtparsers/templates/ReadPrintParserTemplate.h"

class ReadParser : public ReadPrintParserTemplate {
 public:
  explicit ReadParser(ParserContext& context)
      : ReadPrintParserTemplate(context) {}
  [[nodiscard]] std::unique_ptr<TNode> makeTNode() const override;
};
