#pragma once

#include <string>

#include "RelationStore.h"

class UsesPStore : public RelationStore<std::string, std::string> {};
