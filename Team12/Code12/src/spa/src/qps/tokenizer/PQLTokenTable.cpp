#include "PQLTokenTable.h"

PQLTokenTable::PQLTokenTable() {
	for (int i = 0; i < 256; i++)
	{
		tokens[i] = PQL_INVALID_TOKEN;
	}

	tokens[ASCII_TAB] = PQL_IGNORE_TOKEN;
	tokens[ASCII_NEW_LINE] = PQL_IGNORE_TOKEN;
	tokens[ASCII_CARRIAGE_RETURN] = PQL_IGNORE_TOKEN;
	tokens[ASCII_WHITESPACE] = PQL_IGNORE_TOKEN;

	for (int i = ASCII_0; i <= ASCII_9; i++)
	{
		tokens[i] = PQL_INTEGER_TOKEN;
	}

	for (int i = ASCII_LOWER_A; i <= ASCII_LOWER_Z; i++)
	{
		tokens[i] = PQL_CHAR_TOKEN;
	}

	for (int i = ASCII_UPPER_A; i <= ASCII_UPPER_Z; i++)
	{
		tokens[i] = PQL_CHAR_TOKEN;
	}
	
	tokens[ASCII_UNDERSCORE] = PQL_WILDCARD_TOKEN;
	tokens[ASCII_QUOTE] = PQL_QUOTE_TOKEN;
	tokens[ASCII_ROUND_BRACKET_LEFT] = PQL_OPEN_BRACKET_TOKEN;
	tokens[ASCII_ROUND_BRACKET_RIGHT] = PQL_CLOSE_BRACKET_TOKEN;

	tokens[ASCII_TIMES] = PQL_ASTERICKS_TOKEN;
	tokens[ASCII_PLUS] = PQL_OPERATOR_TOKEN;
	tokens[ASCII_MINUS] = PQL_OPERATOR_TOKEN;
	tokens[ASCII_SLASH] = PQL_OPERATOR_TOKEN;

	tokens[ASCII_SEMICOLON] = PQL_SEMICOLON_TOKEN;
	tokens[ASCII_COMMA] = PQL_COMMA_TOKEN;
}

PQLTokenType PQLTokenTable::getTokenType(const char c) {
	return tokens[c];
}
