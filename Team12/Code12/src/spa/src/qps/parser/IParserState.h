#pragma once

#include "qps/exceptions/QPSSemanticError.h"
#include "qps/exceptions/QPSSyntaxError.h"
#include "qps/token/PQLToken.h"

class PQLParserContext;

class IParserState {
 protected:
  virtual void processNameToken(PQLToken& curr) = 0;

 public:
  virtual void handleToken() = 0;
  virtual ~IParserState() = default;
  friend class PQLParserContext;
};
