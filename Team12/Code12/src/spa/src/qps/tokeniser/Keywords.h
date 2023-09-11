#pragma once

#include <string>
#include <vector>
#include <unordered_set>

using std::string, std::vector, std::unordered_set;

const unordered_set<string> designEntities = {
	"stmt",
	"read",
	"print",
	"call",
	"while",
	"if",
	"assign",
	"variable",
	"constant",
	"procedure"
};

const string select = "Select";

const string pattern = "pattern";

const vector<string> suchThat = {
	"such",
	"that"
};
