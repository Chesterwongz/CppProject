#include "DeclarativeClause.h"

#include <utility>

DeclarativeClause::DeclarativeClause(Entity entity, Synonym synonym) :
    entity(std::move(entity)),
    synonym(std::move(synonym)) {}

