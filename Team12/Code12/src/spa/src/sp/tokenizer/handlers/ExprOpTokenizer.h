#pragma once

#include <string>
#include "BaseTokenizer.h"
#include "common/utils/StringUtils.h"
#include "sp/constants/OperatorConstants.h"

class ExprOpTokenizer : public BaseTokenizer {
public:
    Token tokenize(char nextCh, InputStream &inputStream) override;

    static bool matchesExprOp(char ch);
};
