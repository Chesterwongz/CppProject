#pragma once

#include <string>
#include <memory>

#include "qps/argument/IArgument.h"
#include "qps/argument/synonym/Synonym.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"

using std::string;

class ArgumentFactory {
public:
    static std::unique_ptr<IArgument> createArgument(string argument);

    static std::unique_ptr<Synonym> createSynonymArgument(string argumentValue);
    static std::unique_ptr<Ident> createIdentArgument(string argumentValue);
    static std::unique_ptr<Integer> createIntegerArgument(string argumentValue);
    static std::unique_ptr<Wildcard> createWildcardArgument();
};