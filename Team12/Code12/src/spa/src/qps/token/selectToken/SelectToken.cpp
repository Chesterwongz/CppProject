#include "qps/token/selectToken/SelectToken.h"

SelectToken::SelectToken(Synonym synonym) : synonym(synonym) {}

const std::string SelectToken::getSynonym() {
    return synonym;
}