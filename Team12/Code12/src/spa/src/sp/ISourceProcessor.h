#pragma once

#include <string>

class ISourceProcessor {
public:
    virtual ~ISourceProcessor() = default;
    virtual void process(const std::string &fileName) = 0;
};
