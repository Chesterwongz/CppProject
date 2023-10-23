#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "RelationTStore.h"

class CallsSStore : public RelationStore<int, std::string> {};
