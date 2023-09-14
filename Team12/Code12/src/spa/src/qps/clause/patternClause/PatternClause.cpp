#include "PatternClause.h"

#include <utility>

PatternClause::PatternClause(unique_ptr<IArgument> synonym, PatternArgsStreamPtr patternArgsStreamPtr) {
	PatternClause::synonym = std::move(synonym);
}
