#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/tokenizer/TokenStream.h"
#include "qps/parser/tokenizer/handlers/PQLDelimiterTokenizer.h"
#include "qps/parser/tokenizer/handlers/PQLIntegerTokenizer.h"
#include "qps/parser/tokenizer/handlers/PQLLiteralTokenizer.h"
#include "qps/parser/tokenizer/handlers/PQLNameTokenizer.h"
#include "qps/parser/tokenizer/token/PQLToken.h"

typedef TokenStream<PQLToken> PQLTokenStream;

class PQLTokenizer {
 public:
  static std::unique_ptr<TokenStream<PQLToken>> tokenize(string query);
};
