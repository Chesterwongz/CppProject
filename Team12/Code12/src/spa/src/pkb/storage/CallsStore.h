#pragma once

#include <string>

#include "RelationTStore.h"

class CallsStore : public RelationTStore<std::string, std::string> {};
