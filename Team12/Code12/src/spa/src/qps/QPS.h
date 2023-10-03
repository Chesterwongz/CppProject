#pragma once

#include <string>
#include <unordered_set>

#include "pkb/facade/PKBReader.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/token/PQLToken.h"
#include "qps/tokenizer/TokenizerFactory.h"

using std::string;

class QPS {
 private:
  PKBReader& pkb;
  TokenizerFactory tokenizerFactory;
  void setupParser(PQLParserContext& pc);

 public:
  explicit QPS(PKBReader& pkb);
  std::set<string> processQueryString(const string& query);
};
