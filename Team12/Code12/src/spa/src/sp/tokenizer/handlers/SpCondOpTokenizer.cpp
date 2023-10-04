#include "SpCondOpTokenizer.h"

SpToken SpCondOpTokenizer::tokenize(char nextCh, InputStream &inputStream) {
  if (!matchesCondOp(nextCh))
    return BaseTokenizer::tokenize(nextCh, inputStream);

  const std::string value = inputStream.peekWhile(matchesCondOp);
  // Note: ((cond_expr) && !(cond_expr)) is an invalid cond_expr because '&&'
  // and '||' must be followed by a '('.
  if (!isCondOp(value)) return BaseTokenizer::tokenize(nextCh, inputStream);

  inputStream.readN((int)value.length());

  return {SpTokenType::COND_OP, value};
}

bool SpCondOpTokenizer::matchesCondOp(const char ch) {
  // regex("[!&|]")
  return ch == op::kNotChar || ch == op::kAndChar || ch == op::kOrChar;
}

bool SpCondOpTokenizer::isCondOp(const std::string &str) {
  return str == op::kNot || str == op::kAnd || str == op::kOr;
}
