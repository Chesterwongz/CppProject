#pragma once

#include <memory>
#include <string>

#include "common/exceptions/CommonSyntaxError.h"
#include "common/tokenizer/ITokenHandler.h"
#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"
#include "qps/common/PQLParserUtils.h"
#include "qps/common/QPSStringUtils.h"
#include "qps/parser/tokenizer/token/PQLToken.h"

class PQLTokenHandler : public ITokenHandler<PQLToken> {
 private:
  static PQLToken processNameToken(InputStream& inputStream);
  static PQLToken processIntegerToken(InputStream& inputStream);
  static PQLToken processLiteralToken(InputStream& inputStream);
  static PQLToken processDelimiterToken(char nextCh, InputStream& inputStream);

 public:
  PQLToken tokenize(char nextCh, InputStream& inputStream) override;

  inline ITokenHandler<PQLToken>& setNext(
      std::unique_ptr<ITokenHandler<PQLToken>> handler) override {
    return *this;
  }
};
