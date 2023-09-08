#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <memory>

#include "common/utils/StringUtils.h"
#include "qps/tokeniser/Tokeniser.h"
#include "qps/token/QueryToken.h"
#include "qps/token/TokenLinkedList/QueryTokenLL.h"

// Following Factory Method Pattern
// lexical validator + token factory method

using std::string, std::vector, std::unique_ptr, std::unordered_map, std::set;

// the reason for the complex type is because of object slicing
// https://www.geeksforgeeks.org/object-slicing-in-c/
typedef vector<unique_ptr<QueryToken>> TokenStream;
typedef unique_ptr<TokenStream> TokenStreamPtr;

enum FACTORY_TYPES {
    DECLARATIVE,
    SELECT,
    SUCH_THAT,
    PATTERN
};

class TokenFactory;

typedef vector<string> ValidatedTokens;
typedef unique_ptr <vector<string>> UnvalidatedTokenPtr;
typedef unordered_map<FACTORY_TYPES, unique_ptr<TokenFactory>> TokenFactoryPool;

class TokenFactory {
protected:
    const bool isSynonym(const string data);
    const bool isStmtRef(const string data);
    const bool isEntRef(const string data);

    const static set<string> entities; // TODO: Merge with Houten's constants in common or utils folder

    const virtual bool isValid(UnvalidatedTokens unvalidatedTokens) = 0;

public:
    explicit TokenFactory() {};
    ~TokenFactory() {};

    // used like this:
    // DeclarativeTokenFactory* dtf = TokenFactory::getOrCreateFactory();
    // dtf.createToken(validatedTokens);
    virtual TokenStreamPtr createTokens(ValidatedTokens validatedTokens) = 0;

    // for unit-tests; should be under protected
    static TokenFactory* getOrCreateFactory(string keyword);
    static TokenFactoryPool tokenFactories;
};
