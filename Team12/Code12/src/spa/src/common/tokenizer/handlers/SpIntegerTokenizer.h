#pragma once

#include <string>

#include "common/tokenizer/BaseTokenizer.h"
#include "common/tokenizer/token/SpToken.h"
#include "common/utils/StringUtils.h"

class SpIntegerTokenizer : public BaseTokenizer<SpToken> {
 public:
  SpToken tokenize(char nextCh, InputStream &inputStream) override;
};
