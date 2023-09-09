#include "PatternClause.h"

#include <utility>

PatternClause::PatternClause(
        Synonym synonym,
        Reference entRef,
        std::string expression) :
        synonym(std::move(synonym)),
        entRef(entRef),
        expression(std::move(expression)) {}
