#pragma once

#include <iostream>

#include "common/tokenizer/BaseTokenizer.h"
#include "common/utils/StringUtils.h"
#include "qps/common/QPSStringUtils.h"
#include "qps/token/PQLToken.h"

class PQLLiteralTokenizer : public BaseTokenizer<PQLToken> {
 public:
  PQLToken tokenize(char nextCh, InputStream &inputStream);
};
