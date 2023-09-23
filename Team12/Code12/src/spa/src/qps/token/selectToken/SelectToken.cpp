#include "qps/token/selectToken/SelectToken.h"

SelectToken::SelectToken(SynonymType synonym) : synonym(synonym) {}

std::string SelectToken::getSynonym() {
    return synonym;
}

unique_ptr<Clause> SelectToken::buildClause() {
    // by default SelectToken shouldn't be able to build
    return nullptr;
}
