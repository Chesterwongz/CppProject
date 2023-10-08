#pragma once

#include "common/tokenizer/BaseTokenizer.h"
#include "common/tokenizer/token/SpToken.h"
#include "common/utils/StringUtils.h"
#include "sp/constants/OperatorConstants.h"

class SpTermOpTokenizer : public BaseTokenizer<SpToken> {
 private:
  static bool matchesTermOp(char ch);

 public:
  SpToken tokenize(char nextCh, InputStream &inputStream) override;
};
