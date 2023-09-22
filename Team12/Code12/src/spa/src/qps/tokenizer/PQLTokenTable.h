#pragma once

#include "PQLTokenType.h"

// PQL_IGNORE_TOKEN
const int ASCII_TAB = 9;
const int ASCII_NEW_LINE = 10;
const int ASCII_CARRIAGE_RETURN = 13;
const int ASCII_WHITESPACE = 32;

// PQL_INTEGER_TOKEN
const int ASCII_0 = 48;
const int ASCII_9 = 57;

// PQL_NAME_TOKEN
const int ASCII_UPPER_A = 65;
const int ASCII_UPPER_Z = 90;
const int ASCII_LOWER_A = 97;
const int ASCII_LOWER_Z = 122;

// Literals and Arguments
const int ASCII_QUOTE = 34;
const int ASCII_ROUND_BRACKET_LEFT = 40;
const int ASCII_ROUND_BRACKET_RIGHT = 41;

// PQL_WILDCARD_TOKEN
const int ASCII_UNDERSCORE = 95;

// PQL_OPERATOR_TOKEN
const int ASCII_TIMES = 42; // also PQL_ASTERISKS_TOKEN
const int ASCII_PLUS = 43;
const int ASCII_MINUS = 45;
const int ASCII_SLASH = 47;

// PQL_SEMICOLON_TOKEN
const int ASCII_SEMICOLON = 59;

// PQL_COMMA_TOKEN
const int ASCII_COMMA = 44;

// PQL_PERIOD_TOKEN
const int ASCII_PERIOD = 46;



class PQLTokenTable {
private:
	PQLTokenType tokens[256];

public:
	explicit PQLTokenTable();
	PQLTokenType getTokenType(const char c);
};

