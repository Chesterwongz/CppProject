#pragma once

#include <string>
#include "BaseTokenizer.h"
#include "sp/constants/DelimiterConstants.h"

class DelimiterTokenizer : public BaseTokenizer {
private:
    static bool matchesDelim(char ch);
public:
    Token tokenize(char nextCh, std::shared_ptr<InputStream> inputStream) override;

};
