#pragma once

#include <string>
#include <vector>
#include "qps/token/QueryToken.h"

class Tokeniser {
private:


public:
    std::vector<QueryToken> *convertToTokens(std::string &inputString);
};

typedef std::vector<std::string> UnvalidatedTokens;
