#pragma once

#include <string>
#include <memory>

#include "../IArgument.h"
#include "../synonym/Synonym.h"
#include "../ident/Ident.h"
#include "../integer/Integer.h"
#include "../wildcard/Wildcard.h"

using std::string;

class ArgumentFactory {
public:
    static std::unique_ptr<IArgument> createArgument(string argument);

    static std::unique_ptr<Synonym> createSynonymArgument(string argumentValue);
    static std::unique_ptr<Ident> createIdentArgument(string argumentValue);
    static std::unique_ptr<Integer> createIntegerArgument(string argumentValue);
    static std::unique_ptr<Wildcard> createWildcardArgument();
};