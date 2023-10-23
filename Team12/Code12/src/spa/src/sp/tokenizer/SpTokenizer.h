#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/tokenizer/TokenStream.h"
#include "common/tokenizer/handlers/SpCondOpTokenizer.h"
#include "common/tokenizer/handlers/SpDelimiterTokenizer.h"
#include "common/tokenizer/handlers/SpExprOpTokenizer.h"
#include "common/tokenizer/handlers/SpIntegerTokenizer.h"
#include "common/tokenizer/handlers/SpNameTokenizer.h"
#include "common/tokenizer/handlers/SpRelOpTokenizer.h"
#include "common/tokenizer/handlers/SpTermOpTokenizer.h"
#include "sp/utils/FileReaderUtils.h"

class SpTokenizer {
 public:
  static std::unique_ptr<TokenStream<SpToken>> tokenize(string filePath);
};
