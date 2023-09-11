#include "PatternClause.h"

#include <utility>

PatternClause::PatternClause(
        Synonym synonym,
        Reference entRef,
        std::string expression) :
        synonym(synonym),
        entRef(entRef),
        expression(expression) {}
