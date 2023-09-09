#pragma once

#include <string>
#include <vector>

class Clause {
public:
    virtual std::vector<int> evaluate() = 0;
};