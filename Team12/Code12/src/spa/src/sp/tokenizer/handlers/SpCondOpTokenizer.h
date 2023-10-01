#pragma once

#include "common/tokenizer/BaseTokenizer.h"
#include "sp/constants/OperatorConstants.h"
#include "sp/tokenizer/token/SpToken.h"

class SpCondOpTokenizer : public BaseTokenizer<SpToken> {
private:
    static bool matchesCondOp(char ch);

    static bool isCondOp(const string &str);

public:
    SpToken tokenize(char nextCh, InputStream &inputStream) override;
};

