#pragma once

#include <set>
#include <vector>
#include <memory>
#include "qps/argument/AbstractArgument.h"
#include "common/utils/StringUtils.h"
#include "../intermediateTable/IntermediateTableTestData.h"
#include "pkb/facade/PKBReader.h"
#include "../testUtils/argumentFactory/ArgumentFactory.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline PKBStorage MOCK_STORAGE{};

inline string MOCK_SYNONYM_VALUE_1 = "x";
inline string MOCK_SYNONYM_VALUE_2 = "y";

inline string MOCK_IDENT_VALUE_1 = "\"x\"";
inline string MOCK_IDENT_VALUE_2 = "\"y\"";

inline string MOCK_INTEGER_VALUE_1 = "1";
inline string MOCK_INTEGER_VALUE_2 = "2";

inline string MOCK_WILDCARD_VALUE = WILDCARD_KEYWORD;
