#pragma once

#include <string>
#include <memory>

#include "qps/argument/IArgument.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/tokenizer/PQLTokenType.h"

using std::string;

class ArgumentFactory {
public:
    static std::unique_ptr<IArgument> createArgument(string& argument);

    static std::unique_ptr<SynonymArg> createSynonymArgument(const string& argumentValue);
    static std::unique_ptr<Ident> createIdentArgument(const string& argumentValue);
    static std::unique_ptr<Integer> createIntegerArgument(const string& argumentValue);
    static std::unique_ptr<Wildcard> createWildcardArgument();
};
