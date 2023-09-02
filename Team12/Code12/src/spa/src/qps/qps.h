#pragma once

#include "PKB.h"
#include "qps/tokeniser/tokeniser.h"

class QPS {
private:
    static PKB *pkb;
    static Tokeniser *tokeniser;

public:
    void processQueryString(std::string &queryString);
};