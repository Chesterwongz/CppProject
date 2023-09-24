#include "DelimiterTokenizer.h"

Token DelimiterTokenizer::tokenize(char nextCh, InputStream &inputStream) {
    if (!matchesDelim(nextCh)) { // filter non-delimiters
        return BaseTokenizer::tokenize(nextCh, inputStream);
    }

    return {TokenType::DELIM, std::string(1, inputStream.read())};
}

bool DelimiterTokenizer::matchesDelim(const char ch) {
    // regex([;{}()=])
    return ch == delim::kSemicolonChar
           || ch == delim::kOpenCurlyChar || ch == delim::kCloseCurlyChar
           || ch == delim::kOpenBracketChar || ch == delim::kCloseBracketChar
           || ch == delim::kAssignChar;
}