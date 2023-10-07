#pragma once

#include <string>

#include "common/tokenizer/BaseTokenizer.h"
#include "common/tokenizer/token/SpToken.h"
#include "sp/constants/OperatorConstants.h"

class SpRelOpTokenizer : public BaseTokenizer<SpToken> {
 private:
  static bool isRelOp(const string &str);

  static bool matchesRelOp(char ch);

 public:
  SpToken tokenize(char nextCh, InputStream &inputStream) override;
};
