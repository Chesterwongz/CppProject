#pragma once

#include <set>
#include <vector>
#include <memory>
#include "qps/argument/argumentFactory/ArgumentFactory.h"
#include "qps/argument/IArgument.h"
#include "common/utils/StringUtils.h"

using std::set, std::unique_ptr, std::string, std::vector, std::pair;

inline string MOCK_SYNONYM_NAME = "x";
inline unique_ptr<IArgument> getMockSynonymArgument() {
    return ArgumentFactory::createArgument(MOCK_SYNONYM_NAME);
}

inline string MOCK_IDENT_NAME = "\"x\"";
inline unique_ptr<IArgument> getMockIdentArgument() {
    return ArgumentFactory::createArgument(MOCK_IDENT_NAME);
}

inline string MOCK_WILDCARD_NAME = StringUtils::WILDCARD;
inline unique_ptr<IArgument> getMockWildcardArgument() {
    return ArgumentFactory::createArgument(MOCK_WILDCARD_NAME);
}

inline set<string>MOCK_VARIABLES({ "a", "b", "c" });

inline set<string>MOCK_STATEMENTS_SET({"1", "2", "3" });

inline vector<pair<string, string>>MOCK_FOLLOWS_PAIRS(
        {{"follows 1", "follows 2"},
         {"follows 3", "follows 4"},
         {"follows 5", "follows 6"},
         {"follows 7", "follows 8"}});

inline vector<pair<string, string>>MOCK_FOLLOWS_STARS_PAIRS(
        {{"follows stars 1", "follows stars 2"},
         {"follows stars 3", "follows stars 4"},
         {"follows stars 5", "follows stars 6"},
         {"follows stars 7", "follows stars 8"}});

inline vector<pair<string, string>>MOCK_PARENT_CHILD_PAIRS(
        {{"pc 1", "pc 2"},
         {"pc 3", "pc 4"},
         {"pc 5", "pc 6"},
         {"pc 7", "pc 8"}});

inline vector<pair<string, string>>MOCK_PARENT_CHILD_STAR_PAIRS(
        {{"pc star 1",  "pc star 2"},
         {"pc star 3", "pc star 4"},
         {"pc star 5", "pc star 6"},
         {"pc star 7", "pc star 8"}});

inline vector<string>MOCK_MODIFYING_STATEMENTS(
        {"modifying 1",
         "modifying 2",
         "modifying 3"});

inline vector<string>MOCK_USING_STATEMENTS(
        {"using 1",
         "using 2",
         "using 3"});

inline vector<pair<string, string>>MOCK_MODIFIED_PAIRS(
        {{"modifying 1", "modifying 2"},
         {"modifying 3", "modifying 4"},
         {"modifying 5", "modifying 6"},
         {"modifying 7", "modifying 8"}});

inline vector<pair<string, string>>MOCK_USED_PAIRS(
        {{"using 1", "using 2"},
         {"using 3", "using 4"},
         {"using 5", "using 6"},
         {"using 7", "using 8"}});
