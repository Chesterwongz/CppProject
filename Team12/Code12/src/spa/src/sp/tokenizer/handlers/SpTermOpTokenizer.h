#pragma once

#include "common/tokenizer/BaseTokenizer.h"
#include "common/utils/StringUtils.h"
#include "sp/constants/OperatorConstants.h"
#include "sp/tokenizer/token/SpToken.h"

class SpTermOpTokenizer : public BaseTokenizer<SpToken> {
private:
    static bool matchesTermOp(char ch);

public:
    SpToken tokenize(char nextCh, InputStream &inputStream) override;
};
