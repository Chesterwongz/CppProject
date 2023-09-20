#pragma once

#include <string>
#include "BaseTokenizer.h"
#include "common/utils/StringUtils.h"

class IntegerTokenizer : public BaseTokenizer {
public:
    Token tokenize(char nextCh, InputStream &inputStream) override;
};
