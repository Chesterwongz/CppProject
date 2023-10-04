#pragma once

#include <memory>

#include "sp/parser/abstractparser/AbstractParser.h"
#include "sp/parser/terminalparsers//VarParser.h"

class ReadPrintParserTemplate : public AbstractParser {
 public:
  std::optional<std::unique_ptr<TNode>> parse() override;

 protected:
  explicit ReadPrintParserTemplate(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)) {}

  [[nodiscard]] virtual std::unique_ptr<TNode> makeTNode() const = 0;
};
