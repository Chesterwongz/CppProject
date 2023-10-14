#pragma once

#include <string>

#include "RelationStore.h"

class UsesStore : public RelationStore<int, std::string> {};
