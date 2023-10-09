#include "PQLTokenStream.h"

#include "qps/exceptions/QPSInvalidQueryException.h"

PQLTokenStream2::PQLTokenStream2(PQLTokenList& tokenList)
    : tokenList(tokenList) {
  currIndex = 0;
  tokenListSize = tokenList.size();
}

bool PQLTokenStream2::isTokenStreamEnd() const {
  return currIndex >= tokenListSize;
}

void PQLTokenStream2::next() {
  if (!isTokenStreamEnd()) {
    currIndex++;
  }
}

PQLToken& PQLTokenStream2::peek() {
  if (!isTokenStreamEnd()) {
    return tokenList.at(currIndex);
  }
  throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_OUT_OF_BOUNDS);
}

PQLToken& PQLTokenStream2::getCurrentToken() {
  if (isTokenStreamEnd()) {
    throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_OUT_OF_BOUNDS);
  }

  return tokenList.at(currIndex);
}
