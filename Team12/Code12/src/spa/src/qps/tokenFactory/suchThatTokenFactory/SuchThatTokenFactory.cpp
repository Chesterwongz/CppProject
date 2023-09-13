#include "SuchThatTokenFactory.h"
#include "qps/token/suchThatToken/SuchThatToken.h"
#include "../../argument/argumentFactory/ArgumentFactory.h"

using std::string;

bool SuchThatTokenFactory::isValid(UnvalidatedTokens unvalidatedTokens) {
    if (unvalidatedTokens.size() != 2) {
        return false;
    }

    return true;
}

void SuchThatTokenFactory::setRelationship(std::string relationship) {
    SuchThatTokenFactory::relationship = relationship;
}

QPSTokenStreamPtr SuchThatTokenFactory::createTokens(UnvalidatedTokens unvalidatedTokens) {
    
    if (!isValid(unvalidatedTokens)) {
        throw std::runtime_error("Select token stream is invalid");
    }

    if (unvalidatedTokens.empty()) {
        return std::make_unique<QPSTokenStream>();
    }

    QPSTokenStreamPtr suchThatTokens = std::make_unique<QPSTokenStream>();

    string first = unvalidatedTokens[0];
    string second = unvalidatedTokens[1];

    auto token = std::make_unique<SuchThatToken>(this->relationship, first, second);

    suchThatTokens->push_back(std::move(token));

    return suchThatTokens;
}
