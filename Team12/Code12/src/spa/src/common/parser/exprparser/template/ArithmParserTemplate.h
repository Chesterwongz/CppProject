#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/ast/expressions/ExprNodeFactory.h"

class ArithmParserTemplate : public AbstractParser {
 public:
  std::optional<std::unique_ptr<TNode>> parse() override;

 protected:
  explicit ArithmParserTemplate(ParserContext& context)
      : AbstractParser(context) {}

  [[nodiscard]] virtual std::unique_ptr<AbstractParser> getNextParser()
      const = 0;

  [[nodiscard]] virtual SpTokenType getExpectedTokenType() const = 0;

  [[nodiscard]] virtual TNodeType getExpectedTNodeType() const = 0;
};
