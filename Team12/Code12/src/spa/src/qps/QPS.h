#pragma once

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/parser/tokenizer/token/PQLToken.h"

using std::string, std::vector, std::unique_ptr, std::unordered_set;

class QPS {
 private:
  PKBReader& pkb;
  static void setupParser(PQLParserContext& pc);

 public:
  explicit QPS(PKBReader& pkb);
  unordered_set<string> processQueryString(const string& query);
};
