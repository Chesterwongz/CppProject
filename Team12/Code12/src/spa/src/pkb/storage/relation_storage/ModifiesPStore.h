#pragma once

#include <string>

#include "RelationStore.h"

class ModifiesPStore : public RelationStore<std::string, std::string> {};
