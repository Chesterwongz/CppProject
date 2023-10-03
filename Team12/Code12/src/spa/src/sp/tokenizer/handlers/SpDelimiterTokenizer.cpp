#include "SpDelimiterTokenizer.h"

SpToken SpDelimiterTokenizer::tokenize(char nextCh, InputStream &inputStream) {
  if (!matchesDelim(nextCh)) {  // filter non-delimiters
    return BaseTokenizer::tokenize(nextCh, inputStream);
  }

  return {SpTokenType::DELIM, inputStream.read()};
}

bool SpDelimiterTokenizer::matchesDelim(const char ch) {
  // regex([;{}()=])
  return ch == delim::kSemicolonChar || ch == delim::kOpenCurlyChar ||
         ch == delim::kCloseCurlyChar || ch == delim::kOpenBracketChar ||
         ch == delim::kCloseBracketChar || ch == delim::kAssignChar;
}