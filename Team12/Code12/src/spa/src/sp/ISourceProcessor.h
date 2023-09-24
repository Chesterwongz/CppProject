#pragma once

#include <string>
#include "pkb/facade/PKBWriter.h"

class ISourceProcessor {
public:
    virtual ~ISourceProcessor() = default;
    virtual void process(const std::string &fileName, PKBWriter &pkbWriter) = 0;
};
