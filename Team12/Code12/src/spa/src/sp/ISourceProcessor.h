#pragma once

#include <string>

class ISourceProcessor {
public:
    virtual ~ISourceProcessor() = default;
    virtual void process(std::string &fileName) = 0;
};
