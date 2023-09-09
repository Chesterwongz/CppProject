#pragma once

#include <string>
#include <vector>
#include <set>

using std::string;
using std::vector;
using std::set;

const set<string> designEntities = {
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
