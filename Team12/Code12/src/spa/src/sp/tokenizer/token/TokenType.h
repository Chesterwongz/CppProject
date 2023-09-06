#pragma once

#include <unordered_map>

enum class TokenType {
    NAME, // Identifier tokens, aka names
    OP, // Operator tokens, e.g., ">"
    INT, // Constant tokens, aka integers
};
