#pragma once

#include "common/tokenizer/BaseTokenizer.h"
#include "sp/constants/DelimiterConstants.h"
#include "sp/tokenizer/token/SpToken.h"

class SpDelimiterTokenizer : public BaseTokenizer<SpToken> {
private:
    static bool matchesDelim(char ch);

public:
    SpToken tokenize(char nextCh, InputStream &inputStream) override;
};
