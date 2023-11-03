#pragma once

#include <string>

#include "RelationStore.h"

class UsesSStore : public RelationStore<int, std::string> {};
