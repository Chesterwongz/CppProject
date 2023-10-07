#pragma once

#include "common/tokenizer/BaseTokenizer.h"
#include "common/tokenizer/token/SpToken.h"
#include "sp/constants/DelimiterConstants.h"

class SpDelimiterTokenizer : public BaseTokenizer<SpToken> {
 private:
  static bool matchesDelim(char ch);

 public:
  SpToken tokenize(char nextCh, InputStream &inputStream) override;
};
