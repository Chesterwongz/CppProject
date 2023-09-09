#include "SelectClause.h"

#include <utility>

SelectClause::SelectClause(Synonym synonym) : synonym(std::move(synonym)) {}
