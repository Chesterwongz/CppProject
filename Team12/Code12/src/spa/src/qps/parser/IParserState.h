#pragma once

#include <memory>

#include "qps/token/PQLToken.h"

using std::unique_ptr;

class IParserState {
 protected:
  virtual void processNameToken(PQLToken& curr) = 0;

 public:
  virtual void handleToken() = 0;
  virtual ~IParserState() = default;
};
