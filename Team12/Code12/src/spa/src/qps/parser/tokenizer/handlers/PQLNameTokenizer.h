#pragma once

#include "common/tokenizer/BaseTokenizer.h"
#include "common/utils/StringUtils.h"
#include "qps/common/QPSStringUtils.h"
#include "qps/parser/tokenizer/token/PQLToken.h"

class PQLNameTokenizer : public BaseTokenizer<PQLToken> {
 public:
  PQLToken tokenize(char nextCh, InputStream &inputStream);
};
