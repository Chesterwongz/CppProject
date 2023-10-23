#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/parser/abstractparser/AbstractParser.h"
#include "sp/constants/KeywordConstants.h"
#include "sp/parser/stmtparsers/CallParser.h"
#include "sp/parser/stmtparsers/IfParser.h"
#include "sp/parser/stmtparsers/PrintParser.h"
#include "sp/parser/stmtparsers/ReadParser.h"
#include "sp/parser/stmtparsers/WhileParser.h"

class StmtParserFactory {
 public:
  static std::unique_ptr<AbstractParser> makeParser(
      const std::string &keyword, std::shared_ptr<ParserContext>);
};
