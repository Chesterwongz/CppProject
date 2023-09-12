#pragma once

#include "sp/ast/StmtListNode.h"
#include "sp/parser/abstractparser/AbstractParser.h"
#include "sp/parser/stmtparsers/StmtParser.h"

class StmtLstParser : public AbstractParser {
public:
    explicit StmtLstParser(std::shared_ptr<ParserContext> context) : AbstractParser(std::move(context)) {};
    std::optional<std::unique_ptr<TNode>> parse() override;
};
