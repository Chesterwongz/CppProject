#pragma once

#include <string>

#include "RelationTStore.h"

class ModifiesStore : public RelationStore<int, std::string> {};
