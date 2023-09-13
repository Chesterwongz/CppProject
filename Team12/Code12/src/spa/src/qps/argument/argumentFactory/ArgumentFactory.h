#pragma once

#include <string>
#include <memory>

#include "../IArgument.h"

using std::string;

class ArgumentFactory {
public:
    static std::unique_ptr<IArgument> createArgument(string argument);
};