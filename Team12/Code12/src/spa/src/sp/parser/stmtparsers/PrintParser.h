#pragma once

#include <memory>
#include <string>
#include <utility>

#include "sp/ast/statements/PrintNode.h"
#include "sp/parser/stmtparsers/templates/ReadPrintParserTemplate.h"

// print: 'print' var_name';'
class PrintParser : public ReadPrintParserTemplate {
 public:
  explicit PrintParser(ParserContext& context)
      : ReadPrintParserTemplate(context) {}

  [[nodiscard]] std::unique_ptr<TNode> makeTNode() const override;
};
