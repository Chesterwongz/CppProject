#pragma once

#include <string>
#include "BaseTokenizer.h"
#include "sp/constants/OperatorConstants.h"

class RelOpTokenizer : public BaseTokenizer {
private:
    static bool isRelOp(const string &str);

    static bool matchesRelOp(char ch);

public:
    Token tokenize(char nextCh, InputStream &inputStream) override;
};

