#pragma once

#include <string>
#include <vector>
#include "qps/clause/clause.h"

class Token {
private:
    std::vector<std::string> attribute;
    Token *next;

public:
    std::string getAttribute();
    Token *getNext();
    ~Token();

    virtual Token *makeToken() = 0;
    virtual bool validate() = 0;
    virtual Clause *build() = 0;
};
