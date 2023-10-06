#pragma once

#include <memory>

#include "qps/token/PQLToken.h"

class PQLTokenStream {
 private:
  int currIndex;
  int tokenListSize;
  PQLTokenList& tokenList;

 public:
  explicit PQLTokenStream(PQLTokenList& tokenList);
  [[nodiscard]] bool isTokenStreamEnd() const;
  void next();
  PQLToken& getCurrentToken();
  PQLToken& peek();
};
