#include "SuchThatClause.h"

#include <utility>

SuchThatClause::SuchThatClause(
        Abstraction relationship,
        Reference first,
        Reference second) :
        relationship(std::move(relationship)),
        firstArg(first),
        secondArg(second) {}




