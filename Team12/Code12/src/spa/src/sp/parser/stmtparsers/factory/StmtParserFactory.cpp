#include "StmtParserFactory.h"

std::unique_ptr<AbstractParser> StmtParserFactory::makeParser(const string &keyword,
                                                              std::shared_ptr<ParserContext> context) {
    if (keyword == keyword::kRead)
        return std::make_unique<ReadParser>(std::move(context));
    if (keyword == keyword::kPrint)
        return std::make_unique<PrintParser>(std::move(context));
    if (keyword == keyword::kCall)
        return std::make_unique<CallParser>(std::move(context));
    if (keyword == keyword::kIf)
        return std::make_unique<IfParser>(std::move(context));
    if (keyword == keyword::kWhile)
        return std::make_unique<WhileParser>(std::move(context));
    return std::make_unique<AssignParser>(std::move(context), keyword);
}
