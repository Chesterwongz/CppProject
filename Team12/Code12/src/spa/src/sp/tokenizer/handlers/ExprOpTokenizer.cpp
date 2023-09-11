#include "ExprOpTokenizer.h"

Token ExprOpTokenizer::tokenize(char nextCh, std::shared_ptr<InputStream> inputStream) {
    if (!matchesExprOp(nextCh)) { // filter non expression operators
        return BaseTokenizer::tokenize(nextCh, inputStream);
    }

    return {TokenType::EXPR_OP, std::string(1, inputStream->read())};
}

bool ExprOpTokenizer::matchesExprOp(const char ch) {
    // regex("[+-]")
    return ch == op::kPlusChar || ch == op::kMinusChar;
}