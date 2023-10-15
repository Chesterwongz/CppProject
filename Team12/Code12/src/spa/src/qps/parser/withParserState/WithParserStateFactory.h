#pragma once

#include <memory>

#include "qps/parser/PQLParserContext.h"

class WithParserState;

class WithParserStateFactory {
 public:
  inline static std::unique_ptr<WithParserState> createWithParser(
      PQLParserContext& pc) {
    return std::make_unique<WithParserState>(pc, PQL_WITH_TOKEN);
  }
};
