#pragma once

#include "AssignParser.h"
#include "sp/parser/stmtparsers/factory/StmtParserFactory.h"
#include "sp/parser/abstractparser/AbstractParser.h"

class StmtParser : public AbstractParser {
public:
    explicit StmtParser(std::shared_ptr<ParserContext> context) : AbstractParser(std::move(context)) {};

    std::optional<std::unique_ptr<TNode>> parse() override;
};
