#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <memory>

#include "common/utils/StringUtils.h"
#include "qps/token/QueryToken.h"
#include "qps/common/Keywords.h"

// Following Factory Method Pattern
// lexical validator + token factory method

using std::string, std::vector, std::unique_ptr, std::unordered_map, std::set;

// the reason for the complex type is because of object slicing
// https://www.geeksforgeeks.org/object-slicing-in-c/
typedef vector<unique_ptr<QueryToken>> QPSTokenStream;
typedef unique_ptr<QPSTokenStream> QPSTokenStreamPtr; // this needs to be unique_ptr to ensure the lifetime of the tokenstream
typedef vector<string> UnvalidatedTokens;

class TokenFactory;
typedef unordered_map<TOKENTYPES, unique_ptr<TokenFactory>> TokenFactoryPool;

class TokenFactory {
protected:

    const static set<string> entities; // TODO: Merge with Houten's constants in common or utils folder

    virtual bool isValid(UnvalidatedTokens unvalidatedTokens) = 0;

public:
    explicit TokenFactory() = default;
    virtual ~TokenFactory() = default;

    // used like this:
    // DeclarativeTokenFactory* dtf = TokenFactory::getOrCreateFactory();
    // dtf.createToken(validatedTokens);
    virtual QPSTokenStreamPtr createTokens(UnvalidatedTokens unvalidatedTokens) = 0;

    // for unit-tests; should be under protected
    static TokenFactory* getOrCreateFactory(TOKENTYPES keyword);
    static TokenFactoryPool tokenFactories;
};
