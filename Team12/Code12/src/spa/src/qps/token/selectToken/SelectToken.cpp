#include "qps/token/selectToken/SelectToken.h"

SelectToken::SelectToken(Synonym synonym) : synonym(synonym) {}

std::string SelectToken::getSynonym() {
    return synonym;
}


