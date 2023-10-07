#pragma once

#include <memory>
#include <string>
#include <utility>

#include "sp/ast/expressions/ExprNodeFactory.h"
#include "sp/parser/abstractparser/AbstractParser.h"

class ArithmParserTemplate : public AbstractParser {
 public:
  std::optional<std::unique_ptr<TNode>> parse() override;

 protected:
  explicit ArithmParserTemplate(std::shared_ptr<ParserContext> context)
      : AbstractParser(std::move(context)) {}

  [[nodiscard]] virtual std::unique_ptr<AbstractParser> getNextParser()
      const = 0;

  [[nodiscard]] virtual SpTokenType getExpectedTokenType() const = 0;

  [[nodiscard]] virtual TNodeType getExpectedTNodeType() const = 0;
};
