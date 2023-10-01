#include "SpExprOpTokenizer.h"

SpToken SpExprOpTokenizer::tokenize(char nextCh, InputStream &inputStream) {
    if (!matchesExprOp(nextCh)) { // filter non expression operators
        return BaseTokenizer::tokenize(nextCh, inputStream);
    }

    return {SpTokenType::EXPR_OP, inputStream.read()};
}

bool SpExprOpTokenizer::matchesExprOp(const char ch) {
    // regex("[+-]")
    return ch == op::kPlusChar || ch == op::kMinusChar;
}