#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <memory>

#include "../../common/utils/StringUtils.h"
#include "qps/tokeniser/Tokeniser.h"
#include "qps/token/QueryToken.h"
#include "../token/TokenLinkedList/QueryTokenLL.h"

// Following Factory Method Pattern
// lexical validator + token factory method

using std::string, std::vector, std::unique_ptr, std::unordered_map, std::set;

typedef vector<QueryToken> TokenStream;
typedef unique_ptr<TokenStream> TokenStreamPtr;

enum FACTORY_TYPES {
    DECLARATIVE,
    SELECT,
    SUCH_THAT,
    PATTERN
};

typedef vector<string> ValidatedTokens;
typedef unique_ptr <vector<string>> UnvalidatedTokenPtr;
typedef unordered_map<FACTORY_TYPES, unique_ptr<TokenFactory>> TokenFactoryPool;

class TokenFactory {
protected:
    explicit TokenFactory() {};
    ~TokenFactory() {};

    const bool isSynonym(const string data);
    const bool isStmtRef(const string data);
    const bool isEntRef(const string data);

    const static set<string> entities; // TODO: Merge with Houten's constants in common or utils folder

    const virtual bool isValid(UnvalidatedTokens unvalidatedTokens) = 0;

public:
    // used like this:
    // unique_ptr<TokenFactory> tf = TokenFactory.createOrAddFactoryToPool(keyword);
    // tf->createToken(validatedTokens);
    unique_ptr<TokenFactory> createOrAddFactoryToPool(const string keyword);
    virtual TokenStreamPtr createTokens(ValidatedTokens validatedTokens) = 0;

    // for unit-tests; should be under protected
    static TokenFactoryPool tokenFactories;
};
