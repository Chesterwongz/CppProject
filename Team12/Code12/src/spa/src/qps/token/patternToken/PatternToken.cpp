#include "qps/token/patternToken/PatternToken.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/argument/IArgument.h"
#include "qps/argument/argumentFactory/ArgumentFactory.h"

PatternToken::PatternToken(string synonym, vector<string> unvalidatedTokens) {
    PatternToken::synonym = ArgumentFactory::createArgument(synonym);
    for (int i = 0; i < unvalidatedTokens.size(); i++) {
        unique_ptr<IArgument> arg = ArgumentFactory::createArgument(unvalidatedTokens[i]);
        PatternToken::patternArgsStreamPtr->push_back(arg);
    }
}

Synonym PatternToken::getSynonym() {
    return synonym->getValue();
}

//Reference PatternToken::getFirstArgument() {
//    return entRef;
//}
//
//std::string PatternToken::getExpression() {
//    return expression;
//}

unique_ptr<vector<unique_ptr<IArgument>>> PatternToken::getPatternArgsStreamPtr() {
    return std::move(patternArgsStreamPtr);
}

unique_ptr<Clause> PatternToken::buildClause() {
    return std::make_unique<PatternClause>(std::move(synonym), std::move(patternArgsStreamPtr));
}
