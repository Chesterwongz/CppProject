#pragma once

#include "sp/ast/statements/AssignNode.h"
#include "sp/parser/abstractparser/AbstractParser.h"
#include "sp/parser/exprparser/ExprParser.h"
#include "sp/parser/terminalparsers/VarParser.h"

class AssignParser : public AbstractParser {
private:
    std::string varName;
public:
    explicit AssignParser(std::shared_ptr<ParserContext> context, std::string varName)
            : AbstractParser(std::move(context)), varName(std::move(varName)) {};

    std::optional<std::unique_ptr<TNode>> parse() override;
};
