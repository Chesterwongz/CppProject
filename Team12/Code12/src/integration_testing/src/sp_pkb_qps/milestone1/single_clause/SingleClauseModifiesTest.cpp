#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <set>

#include <catch.hpp>
#include "sp/SourceProcessor.h"
#include "pkb/facade/PKB.h"
#include "qps/QPS.h"

using std::string, std::unordered_map, std::map, std::unordered_set, std::set,
std::vector, std::pair;

string modifiesSource = "";
