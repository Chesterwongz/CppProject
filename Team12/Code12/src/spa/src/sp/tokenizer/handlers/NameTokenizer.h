#pragma once

#include <string>
#include "BaseTokenizer.h"
#include "common/utils/StringUtils.h"

class NameTokenizer : public BaseTokenizer {
public:
    Token tokenize(char nextCh, std::shared_ptr<InputStream> inputStream) override;
};
