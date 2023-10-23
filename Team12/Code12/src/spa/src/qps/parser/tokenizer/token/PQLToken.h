#pragma once

#include <memory>
#include <string>
#include <vector>

#include "qps/parser/tokenizer/PQLTokenType.h"

using std::string, std::vector, std::unique_ptr;

typedef string TokenValue;

class PQLToken {
 private:
  PQLTokenType type;
  TokenValue value;

 protected:
  explicit PQLToken(PQLTokenType type);

 public:
  PQLTokenType getType();
  TokenValue getValue();
  void updateTokenType(PQLTokenType tokenType);
  PQLToken(PQLTokenType type, TokenValue value);
};

typedef vector<PQLToken> PQLTokenList;
