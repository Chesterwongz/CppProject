#pragma once

#include <memory>
#include <string>
#include <utility>

#include "FactorParser.h"
#include "common/parser/exprparser/template/ArithmParserTemplate.h"

class TermParser : public ArithmParserTemplate {
 public:
  explicit TermParser(ParserContext& context)
      : ArithmParserTemplate(context) {}

 protected:
  [[nodiscard]] std::unique_ptr<AbstractParser> getNextParser() const override;

  [[nodiscard]] SpTokenType getExpectedTokenType() const override;

  [[nodiscard]] TNodeType getExpectedTNodeType() const override;
};
