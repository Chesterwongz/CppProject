#include "../../argument/argumentFactory/ArgumentFactory.h"
#include "PatternTokenFactory.h"
#include "../../token/patternToken/PatternToken.h"
#include "../../../common/utils/StringUtils.h"

using std::string;

bool PatternTokenFactory::isValid(UnvalidatedTokens unvalidatedTokens) {
    if (unvalidatedTokens.size() == 2 || unvalidatedTokens.size() == 3) {
        return true;
    }

    return false;
}

void PatternTokenFactory::setSynonym(std::string synonym) {
    PatternTokenFactory::synonym = synonym;
}

QPSTokenStreamPtr PatternTokenFactory::createTokens(UnvalidatedTokens unvalidatedTokens) {

    if (!isValid(unvalidatedTokens)) {
        throw std::runtime_error("Select token stream is invalid");
    }

    if (unvalidatedTokens.empty()) {
        return std::make_unique<QPSTokenStream>();
    }

    QPSTokenStreamPtr patternTokens = std::make_unique<QPSTokenStream>();

    auto token = std::make_unique<PatternToken>(this->synonym, unvalidatedTokens);

    patternTokens->push_back(std::move(token));

    return patternTokens;
}
