#pragma once

#include "FactorParser.h"
#include "sp/parser/exprparser/template/ArithmParserTemplate.h"

class TermParser : public ArithmParserTemplate {
public:
    explicit TermParser(std::shared_ptr<ParserContext> context) : ArithmParserTemplate(std::move(context)) {};
protected:
    [[nodiscard]] std::unique_ptr<AbstractParser> getNextParser() const override;

    [[nodiscard]] SpTokenType getExpectedTokenType() const override;

    [[nodiscard]] TNodeType getExpectedTNodeType() const override;
};
