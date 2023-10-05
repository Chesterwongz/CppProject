#pragma once

#include "common/tokenizer/BaseTokenizer.h"
#include "sp/constants/OperatorConstants.h"
#include "sp/tokenizer/token/SpToken.h"

class SpExprOpTokenizer : public BaseTokenizer<SpToken> {
 private:
  static bool matchesExprOp(char ch);

 public:
  SpToken tokenize(char nextCh, InputStream &inputStream) override;
};
