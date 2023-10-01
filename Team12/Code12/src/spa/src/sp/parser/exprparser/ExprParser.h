#pragma once

#include "TermParser.h"
#include "sp/parser/exprparser/template/ArithmParserTemplate.h"

class ExprParser : public ArithmParserTemplate {
public:
    explicit ExprParser(std::shared_ptr<ParserContext> context) : ArithmParserTemplate(std::move(context)) {}

protected:
    [[nodiscard]] std::unique_ptr<AbstractParser> getNextParser() const override;

    [[nodiscard]] SpTokenType getExpectedTokenType() const override;

    [[nodiscard]] TNodeType getExpectedTNodeType() const override;
};
