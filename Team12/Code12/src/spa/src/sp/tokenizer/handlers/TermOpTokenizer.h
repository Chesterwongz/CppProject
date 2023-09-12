#pragma once

#include <string>
#include "BaseTokenizer.h"
#include "common/utils/StringUtils.h"
#include "sp/constants/OperatorConstants.h"

class TermOpTokenizer : public BaseTokenizer {
private:
    static bool matchesTermOp(char ch);
public:
    Token tokenize(char nextCh, std::shared_ptr<InputStream> inputStream) override;
};
