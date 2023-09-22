#include "TermOpTokenizer.h"

Token TermOpTokenizer::tokenize(char nextCh, InputStream &inputStream) {
    if (!matchesTermOp(nextCh)) { // filter non term operators
        return BaseTokenizer::tokenize(nextCh, inputStream);
    }

    return {TokenType::TERM_OP, std::string(1, inputStream.read())};
}

bool TermOpTokenizer::matchesTermOp(const char ch) {
    // regex("[*/%]")
    return ch == op::kTimesChar || ch == op::kDivChar || ch == op::kModChar;
}