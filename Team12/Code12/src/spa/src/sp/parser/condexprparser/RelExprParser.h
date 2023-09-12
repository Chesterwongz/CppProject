#pragma once

#include "sp/parser/abstractparser/AbstractParser.h"
#include "sp/parser/condexprparser/RelFactorParser.h"

class RelExprParser : public AbstractParser {
public:
    explicit RelExprParser(std::shared_ptr<ParserContext> context) : AbstractParser(std::move(context)) {}
    std::optional<std::unique_ptr<TNode>> parse() override;
};
