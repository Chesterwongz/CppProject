#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/token/PQLToken.h"
#include "qps/tokenizer/TokenizerFactory.h"

using std::string, std::vector, std::unique_ptr;

class QPS {
 private:
  PKBReader& pkb;
  TokenizerFactory tokenizerFactory;
  void setupParser(PQLParserContext& pc);

 public:
  explicit QPS(PKBReader& pkb);
  std::set<string> processQueryString(const string& query);
};
