#pragma once

#include <memory>
#include <utility>

#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/parser/terminalparsers//VarParser.h"

class ReadPrintParserTemplate : public AbstractParser {
 public:
  std::optional<std::unique_ptr<TNode>> parse() override;

 protected:
  explicit ReadPrintParserTemplate(ParserContext& context)
      : AbstractParser(context) {}

  [[nodiscard]] virtual std::unique_ptr<TNode> makeTNode() const = 0;
};
