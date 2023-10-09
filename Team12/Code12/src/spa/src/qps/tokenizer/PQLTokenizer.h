#pragma once

#include <memory>
#include <string>

#include "PQLTokenTable.h"
#include "common/tokenizer/TokenStream.h"
#include "qps/token/PQLToken.h"
#include "qps/tokenizer/handlers/PQLDelimiterTokenizer.h"
#include "qps/tokenizer/handlers/PQLIntegerTokenizer.h"
#include "qps/tokenizer/handlers/PQLLiteralTokenizer.h"
#include "qps/tokenizer/handlers/PQLNameTokenizer.h"

typedef TokenStream<PQLToken> PQLTokenStream;

class PQLTokenizer {
 public:
  static std::unique_ptr<TokenStream<PQLToken>> tokenize(string query);
};
