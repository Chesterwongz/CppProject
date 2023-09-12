#pragma once

#include "sp/ast/statements/PrintNode.h"
#include "sp/ast/terminals/VarNode.h"
#include "sp/parser/abstractparser/AbstractParser.h"
#include "sp/parser/terminalparsers/VarParser.h"

class PrintParser : public AbstractParser {
public:
    explicit PrintParser(std::shared_ptr<ParserContext> context) : AbstractParser(std::move(context)) {};

    std::optional<std::unique_ptr<TNode>> parse() override;
};
