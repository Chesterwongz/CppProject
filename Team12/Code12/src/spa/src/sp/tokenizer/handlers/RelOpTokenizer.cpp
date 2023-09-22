#include "RelOpTokenizer.h"

Token RelOpTokenizer::tokenize(char nextCh, InputStream &inputStream) {
    if (!matchesRelOp(nextCh))
        return BaseTokenizer::tokenize(nextCh, inputStream);
    const std::string value = inputStream.peekWhile(matchesRelOp);

    if (!isRelOp(value))
        return BaseTokenizer::tokenize(nextCh, inputStream);

    inputStream.readN((int) value.length());

    return {TokenType::REL_OP, value};
}

bool RelOpTokenizer::matchesRelOp(const char ch) {
    // regex("[=<>!]")
    return ch == op::kEqChar || ch == op::kLtChar || ch == op::kGtChar || ch == op::kNotChar;
}

bool RelOpTokenizer::isRelOp(const std::string &str) {
    return str == op::kGt || str == op::kLt || str == op::kGte || str == op::kLte || str == op::kEq || str == op::kNeq;
}