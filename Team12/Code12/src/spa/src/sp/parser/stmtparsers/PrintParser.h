#pragma once

#include "sp/ast/statements/PrintNode.h"
#include "sp/parser/stmtparsers/templates/ReadPrintParserTemplate.h"

// print: 'print' var_name';'
class PrintParser : public ReadPrintParserTemplate {
 public:
  explicit PrintParser(std::shared_ptr<ParserContext> context)
      : ReadPrintParserTemplate(std::move(context)){};

  [[nodiscard]] std::unique_ptr<TNode> makeTNode() const override;
};
