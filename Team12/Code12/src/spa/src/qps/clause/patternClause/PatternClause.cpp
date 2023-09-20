#include "PatternClause.h"

#include <utility>

PatternClause::PatternClause(
        Synonym synonym,
        Reference entRef,
        std::string expression) :
        synonym(synonym),
        entRef(entRef),
        expression(expression) {}

std::unordered_set<int> PatternClause::evaluate(Context context, PKBReader &pkb) {
    return {};
}