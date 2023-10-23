#pragma once

#include "common/tokenizer/BaseTokenizer.h"
#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"
#include "qps/common/PQLParserUtils.h"
#include "qps/common/QPSStringUtils.h"
#include "qps/parser/tokenizer/token/PQLToken.h"

class PQLDelimiterTokenizer : public BaseTokenizer<PQLToken> {
 public:
  PQLToken tokenize(char nextCh, InputStream &inputStream) override;
};