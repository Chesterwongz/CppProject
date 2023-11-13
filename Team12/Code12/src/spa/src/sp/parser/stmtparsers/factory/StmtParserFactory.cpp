#include "StmtParserFactory.h"

std::unique_ptr<AbstractParser> StmtParserFactory::makeParser(
    const string &keyword, ParserContext& context) {
  if (keyword == keyword::kRead)
    return std::make_unique<ReadParser>(context);
  if (keyword == keyword::kPrint)
    return std::make_unique<PrintParser>(context);
  if (keyword == keyword::kCall)
    return std::make_unique<CallParser>(context);
  if (keyword == keyword::kIf)
    return std::make_unique<IfParser>(context);
  if (keyword == keyword::kWhile)
    return std::make_unique<WhileParser>(context);
  return std::make_unique<AssignParser>(context, keyword);
}
