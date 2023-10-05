#pragma once

#include <memory>
#include <string>

#include "qps/tokenizer/PQLTokenizer.h"

using std::unique_ptr;

class TokenizerFactory {
 public:
  unique_ptr<PQLTokenizer> makeTokenizer(const string& query);
  TokenizerFactory() = default;
};
