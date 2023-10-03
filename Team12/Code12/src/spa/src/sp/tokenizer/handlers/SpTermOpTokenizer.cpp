#include "SpTermOpTokenizer.h"

SpToken SpTermOpTokenizer::tokenize(char nextCh, InputStream &inputStream) {
  if (!matchesTermOp(nextCh)) {  // filter non term operators
    return BaseTokenizer::tokenize(nextCh, inputStream);
  }

  return {SpTokenType::TERM_OP, inputStream.read()};
}

bool SpTermOpTokenizer::matchesTermOp(const char ch) {
  // regex("[*/%]")
  return ch == op::kTimesChar || ch == op::kDivChar || ch == op::kModChar;
}