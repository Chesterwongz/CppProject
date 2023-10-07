#pragma once

#include <string>

#include "common/tokenizer/BaseTokenizer.h"
#include "common/tokenizer/token/SpToken.h"
#include "sp/constants/OperatorConstants.h"

class SpCondOpTokenizer : public BaseTokenizer<SpToken> {
 private:
  static bool matchesCondOp(char ch);

  static bool isCondOp(const string &str);

 public:
  SpToken tokenize(char nextCh, InputStream &inputStream) override;
};
