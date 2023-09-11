#pragma once

#include <string>
#include <vector>

class Clause {
private:
    std::string attribute;

public:
    std::string getAttribute();
    virtual std::vector<int> evaluate() = 0;
};
