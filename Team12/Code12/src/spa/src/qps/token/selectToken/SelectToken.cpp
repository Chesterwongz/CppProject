#include "qps/token/selectToken/SelectToken.h"
#include "qps/clause/selectClause/SelectClause.h"

SelectToken::SelectToken(Synonym synonym) : synonym(synonym) {}

std::string SelectToken::getSynonym() {
    return synonym;
}

unique_ptr<Clause> SelectToken::buildClause() {
    return make_unique<SelectClause>(SelectToken::synonym);
}
