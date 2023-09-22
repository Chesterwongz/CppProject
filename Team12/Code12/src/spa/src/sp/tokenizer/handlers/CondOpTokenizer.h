#pragma once

#include <string>
#include "BaseTokenizer.h"
#include "sp/constants/OperatorConstants.h"

class CondOpTokenizer : public BaseTokenizer {
private:
    static bool matchesCondOp(char ch);

    static bool isCondOp(const string &str);

public:
    Token tokenize(char nextCh, InputStream &inputStream) override;
};

