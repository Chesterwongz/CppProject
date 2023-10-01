#pragma once

#include <set>
#include <string>
#include <vector>

using std::set, std::string, std::vector;

inline set<string> MOCK_EMPTY_RESULT = {};

inline set<string> MOCK_SELECT_CLAUSE_DATA = {"a", "b", "c", "d", "e" };
inline set<string> MOCK_SELECT_CLAUSE_DATA_2 = {"a2", "b2", "c2", "d2", "e2" };
inline set<string> MOCK_SELECT_CLAUSE_DATA_3 = {"a3", "b3", "c3", "d3", "e3" };
inline set<string> MOCK_SELECT_CLAUSE_DATA_4 = {"a4", "b4", "c4", "d4", "e4" };

inline set<string> MOCK_RESULTS_1_COL
        = { "a", "b", "c", "d", "e" };

inline set<string> MOCK_RESULTS_2_COL
        = { "a a", "a b", "a c", "a d", "a e",
            "b a", "b b", "b c", "b d", "b e",
            "c a", "c b", "c c", "c d", "c e",
            "d a", "d b", "d c", "d d", "d e",
            "e a", "e b", "e c", "e d", "e e" };

inline set<string> MOCK_RESULTS_2_COL_2
        = { "a a2", "a b2", "a c2", "a d2", "a e2",
            "b a2", "b b2", "b c2", "b d2", "b e2",
            "c a2", "c b2", "c c2", "c d2", "c e2",
            "d a2", "d b2", "d c2", "d d2", "d e2",
            "e a2", "e b2", "e c2", "e d2", "e e2" };

inline set<string> MOCK_ALL_COL 
        = { "a a2 a3 a4", "a a2 a3 b4", "a a2 a3 c4", "a a2 a3 d4", "a a2 a3 e4",
            "a a2 b3 a4", "a a2 b3 b4", "a a2 b3 c4", "a a2 b3 d4", "a a2 b3 e4",
            "a a2 c3 a4", "a a2 c3 b4", "a a2 c3 c4", "a a2 c3 d4", "a a2 c3 e4",
            "a a2 d3 a4", "a a2 d3 b4", "a a2 d3 c4", "a a2 d3 d4", "a a2 d3 e4",
            "a a2 e3 a4", "a a2 e3 b4", "a a2 e3 c4", "a a2 e3 d4", "a a2 e3 e4",
            "a b2 a3 a4", "a b2 a3 b4", "a b2 a3 c4", "a b2 a3 d4", "a b2 a3 e4",
            "a b2 b3 a4", "a b2 b3 b4", "a b2 b3 c4", "a b2 b3 d4", "a b2 b3 e4",
            "a b2 c3 a4", "a b2 c3 b4", "a b2 c3 c4", "a b2 c3 d4", "a b2 c3 e4",
            "a b2 d3 a4", "a b2 d3 b4", "a b2 d3 c4", "a b2 d3 d4", "a b2 d3 e4",
            "a b2 e3 a4", "a b2 e3 b4", "a b2 e3 c4", "a b2 e3 d4", "a b2 e3 e4",
            "a c2 a3 a4", "a c2 a3 b4", "a c2 a3 c4", "a c2 a3 d4", "a c2 a3 e4",
            "a c2 b3 a4", "a c2 b3 b4", "a c2 b3 c4", "a c2 b3 d4", "a c2 b3 e4",
            "a c2 c3 a4", "a c2 c3 b4", "a c2 c3 c4", "a c2 c3 d4", "a c2 c3 e4",
            "a c2 d3 a4", "a c2 d3 b4", "a c2 d3 c4", "a c2 d3 d4", "a c2 d3 e4",
            "a c2 e3 a4", "a c2 e3 b4", "a c2 e3 c4", "a c2 e3 d4", "a c2 e3 e4",
            "a d2 a3 a4", "a d2 a3 b4", "a d2 a3 c4", "a d2 a3 d4", "a d2 a3 e4",
            "a d2 b3 a4", "a d2 b3 b4", "a d2 b3 c4", "a d2 b3 d4", "a d2 b3 e4",
            "a d2 c3 a4", "a d2 c3 b4", "a d2 c3 c4", "a d2 c3 d4", "a d2 c3 e4",
            "a d2 d3 a4", "a d2 d3 b4", "a d2 d3 c4", "a d2 d3 d4", "a d2 d3 e4",
            "a d2 e3 a4", "a d2 e3 b4", "a d2 e3 c4", "a d2 e3 d4", "a d2 e3 e4",
            "a e2 a3 a4", "a e2 a3 b4", "a e2 a3 c4", "a e2 a3 d4", "a e2 a3 e4",
            "a e2 b3 a4", "a e2 b3 b4", "a e2 b3 c4", "a e2 b3 d4", "a e2 b3 e4",
            "a e2 c3 a4", "a e2 c3 b4", "a e2 c3 c4", "a e2 c3 d4", "a e2 c3 e4",
            "a e2 d3 a4", "a e2 d3 b4", "a e2 d3 c4", "a e2 d3 d4", "a e2 d3 e4",
            "a e2 e3 a4", "a e2 e3 b4", "a e2 e3 c4", "a e2 e3 d4", "a e2 e3 e4",
            "b a2 a3 a4", "b a2 a3 b4", "b a2 a3 c4", "b a2 a3 d4", "b a2 a3 e4",
            "b a2 b3 a4", "b a2 b3 b4", "b a2 b3 c4", "b a2 b3 d4", "b a2 b3 e4",
            "b a2 c3 a4", "b a2 c3 b4", "b a2 c3 c4", "b a2 c3 d4", "b a2 c3 e4",
            "b a2 d3 a4", "b a2 d3 b4", "b a2 d3 c4", "b a2 d3 d4", "b a2 d3 e4",
            "b a2 e3 a4", "b a2 e3 b4", "b a2 e3 c4", "b a2 e3 d4", "b a2 e3 e4",
            "b b2 a3 a4", "b b2 a3 b4", "b b2 a3 c4", "b b2 a3 d4", "b b2 a3 e4",
            "b b2 b3 a4", "b b2 b3 b4", "b b2 b3 c4", "b b2 b3 d4", "b b2 b3 e4",
            "b b2 c3 a4", "b b2 c3 b4", "b b2 c3 c4", "b b2 c3 d4", "b b2 c3 e4",
            "b b2 d3 a4", "b b2 d3 b4", "b b2 d3 c4", "b b2 d3 d4", "b b2 d3 e4",
            "b b2 e3 a4", "b b2 e3 b4", "b b2 e3 c4", "b b2 e3 d4", "b b2 e3 e4",
            "b c2 a3 a4", "b c2 a3 b4", "b c2 a3 c4", "b c2 a3 d4", "b c2 a3 e4",
            "b c2 b3 a4", "b c2 b3 b4", "b c2 b3 c4", "b c2 b3 d4", "b c2 b3 e4",
            "b c2 c3 a4", "b c2 c3 b4", "b c2 c3 c4", "b c2 c3 d4", "b c2 c3 e4",
            "b c2 d3 a4", "b c2 d3 b4", "b c2 d3 c4", "b c2 d3 d4", "b c2 d3 e4",
            "b c2 e3 a4", "b c2 e3 b4", "b c2 e3 c4", "b c2 e3 d4", "b c2 e3 e4",
            "b d2 a3 a4", "b d2 a3 b4", "b d2 a3 c4", "b d2 a3 d4", "b d2 a3 e4",
            "b d2 b3 a4", "b d2 b3 b4", "b d2 b3 c4", "b d2 b3 d4", "b d2 b3 e4",
            "b d2 c3 a4", "b d2 c3 b4", "b d2 c3 c4", "b d2 c3 d4", "b d2 c3 e4",
            "b d2 d3 a4", "b d2 d3 b4", "b d2 d3 c4", "b d2 d3 d4", "b d2 d3 e4",
            "b d2 e3 a4", "b d2 e3 b4", "b d2 e3 c4", "b d2 e3 d4", "b d2 e3 e4",
            "b e2 a3 a4", "b e2 a3 b4", "b e2 a3 c4", "b e2 a3 d4", "b e2 a3 e4",
            "b e2 b3 a4", "b e2 b3 b4", "b e2 b3 c4", "b e2 b3 d4", "b e2 b3 e4",
            "b e2 c3 a4", "b e2 c3 b4", "b e2 c3 c4", "b e2 c3 d4", "b e2 c3 e4",
            "b e2 d3 a4", "b e2 d3 b4", "b e2 d3 c4", "b e2 d3 d4", "b e2 d3 e4",
            "b e2 e3 a4", "b e2 e3 b4", "b e2 e3 c4", "b e2 e3 d4", "b e2 e3 e4",
            "c a2 a3 a4", "c a2 a3 b4", "c a2 a3 c4", "c a2 a3 d4", "c a2 a3 e4",
            "c a2 b3 a4", "c a2 b3 b4", "c a2 b3 c4", "c a2 b3 d4", "c a2 b3 e4",
            "c a2 c3 a4", "c a2 c3 b4", "c a2 c3 c4", "c a2 c3 d4", "c a2 c3 e4",
            "c a2 d3 a4", "c a2 d3 b4", "c a2 d3 c4", "c a2 d3 d4", "c a2 d3 e4",
            "c a2 e3 a4", "c a2 e3 b4", "c a2 e3 c4", "c a2 e3 d4", "c a2 e3 e4",
            "c b2 a3 a4", "c b2 a3 b4", "c b2 a3 c4", "c b2 a3 d4", "c b2 a3 e4",
            "c b2 b3 a4", "c b2 b3 b4", "c b2 b3 c4", "c b2 b3 d4", "c b2 b3 e4",
            "c b2 c3 a4", "c b2 c3 b4", "c b2 c3 c4", "c b2 c3 d4", "c b2 c3 e4",
            "c b2 d3 a4", "c b2 d3 b4", "c b2 d3 c4", "c b2 d3 d4", "c b2 d3 e4",
            "c b2 e3 a4", "c b2 e3 b4", "c b2 e3 c4", "c b2 e3 d4", "c b2 e3 e4",
            "c c2 a3 a4", "c c2 a3 b4", "c c2 a3 c4", "c c2 a3 d4", "c c2 a3 e4",
            "c c2 b3 a4", "c c2 b3 b4", "c c2 b3 c4", "c c2 b3 d4", "c c2 b3 e4",
            "c c2 c3 a4", "c c2 c3 b4", "c c2 c3 c4", "c c2 c3 d4", "c c2 c3 e4",
            "c c2 d3 a4", "c c2 d3 b4", "c c2 d3 c4", "c c2 d3 d4", "c c2 d3 e4",
            "c c2 e3 a4", "c c2 e3 b4", "c c2 e3 c4", "c c2 e3 d4", "c c2 e3 e4",
            "c d2 a3 a4", "c d2 a3 b4", "c d2 a3 c4", "c d2 a3 d4", "c d2 a3 e4",
            "c d2 b3 a4", "c d2 b3 b4", "c d2 b3 c4", "c d2 b3 d4", "c d2 b3 e4",
            "c d2 c3 a4", "c d2 c3 b4", "c d2 c3 c4", "c d2 c3 d4", "c d2 c3 e4",
            "c d2 d3 a4", "c d2 d3 b4", "c d2 d3 c4", "c d2 d3 d4", "c d2 d3 e4",
            "c d2 e3 a4", "c d2 e3 b4", "c d2 e3 c4", "c d2 e3 d4", "c d2 e3 e4",
            "c e2 a3 a4", "c e2 a3 b4", "c e2 a3 c4", "c e2 a3 d4", "c e2 a3 e4",
            "c e2 b3 a4", "c e2 b3 b4", "c e2 b3 c4", "c e2 b3 d4", "c e2 b3 e4",
            "c e2 c3 a4", "c e2 c3 b4", "c e2 c3 c4", "c e2 c3 d4", "c e2 c3 e4",
            "c e2 d3 a4", "c e2 d3 b4", "c e2 d3 c4", "c e2 d3 d4", "c e2 d3 e4",
            "c e2 e3 a4", "c e2 e3 b4", "c e2 e3 c4", "c e2 e3 d4", "c e2 e3 e4",
            "d a2 a3 a4", "d a2 a3 b4", "d a2 a3 c4", "d a2 a3 d4", "d a2 a3 e4",
            "d a2 b3 a4", "d a2 b3 b4", "d a2 b3 c4", "d a2 b3 d4", "d a2 b3 e4",
            "d a2 c3 a4", "d a2 c3 b4", "d a2 c3 c4", "d a2 c3 d4", "d a2 c3 e4",
            "d a2 d3 a4", "d a2 d3 b4", "d a2 d3 c4", "d a2 d3 d4", "d a2 d3 e4",
            "d a2 e3 a4", "d a2 e3 b4", "d a2 e3 c4", "d a2 e3 d4", "d a2 e3 e4",
            "d b2 a3 a4", "d b2 a3 b4", "d b2 a3 c4", "d b2 a3 d4", "d b2 a3 e4",
            "d b2 b3 a4", "d b2 b3 b4", "d b2 b3 c4", "d b2 b3 d4", "d b2 b3 e4",
            "d b2 c3 a4", "d b2 c3 b4", "d b2 c3 c4", "d b2 c3 d4", "d b2 c3 e4",
            "d b2 d3 a4", "d b2 d3 b4", "d b2 d3 c4", "d b2 d3 d4", "d b2 d3 e4",
            "d b2 e3 a4", "d b2 e3 b4", "d b2 e3 c4", "d b2 e3 d4", "d b2 e3 e4",
            "d c2 a3 a4", "d c2 a3 b4", "d c2 a3 c4", "d c2 a3 d4", "d c2 a3 e4",
            "d c2 b3 a4", "d c2 b3 b4", "d c2 b3 c4", "d c2 b3 d4", "d c2 b3 e4",
            "d c2 c3 a4", "d c2 c3 b4", "d c2 c3 c4", "d c2 c3 d4", "d c2 c3 e4",
            "d c2 d3 a4", "d c2 d3 b4", "d c2 d3 c4", "d c2 d3 d4", "d c2 d3 e4",
            "d c2 e3 a4", "d c2 e3 b4", "d c2 e3 c4", "d c2 e3 d4", "d c2 e3 e4",
            "d d2 a3 a4", "d d2 a3 b4", "d d2 a3 c4", "d d2 a3 d4", "d d2 a3 e4",
            "d d2 b3 a4", "d d2 b3 b4", "d d2 b3 c4", "d d2 b3 d4", "d d2 b3 e4",
            "d d2 c3 a4", "d d2 c3 b4", "d d2 c3 c4", "d d2 c3 d4", "d d2 c3 e4",
            "d d2 d3 a4", "d d2 d3 b4", "d d2 d3 c4", "d d2 d3 d4", "d d2 d3 e4",
            "d d2 e3 a4", "d d2 e3 b4", "d d2 e3 c4", "d d2 e3 d4", "d d2 e3 e4",
            "d e2 a3 a4", "d e2 a3 b4", "d e2 a3 c4", "d e2 a3 d4", "d e2 a3 e4",
            "d e2 b3 a4", "d e2 b3 b4", "d e2 b3 c4", "d e2 b3 d4", "d e2 b3 e4",
            "d e2 c3 a4", "d e2 c3 b4", "d e2 c3 c4", "d e2 c3 d4", "d e2 c3 e4",
            "d e2 d3 a4", "d e2 d3 b4", "d e2 d3 c4", "d e2 d3 d4", "d e2 d3 e4",
            "d e2 e3 a4", "d e2 e3 b4", "d e2 e3 c4", "d e2 e3 d4", "d e2 e3 e4",
            "e a2 a3 a4", "e a2 a3 b4", "e a2 a3 c4", "e a2 a3 d4", "e a2 a3 e4",
            "e a2 b3 a4", "e a2 b3 b4", "e a2 b3 c4", "e a2 b3 d4", "e a2 b3 e4",
            "e a2 c3 a4", "e a2 c3 b4", "e a2 c3 c4", "e a2 c3 d4", "e a2 c3 e4",
            "e a2 d3 a4", "e a2 d3 b4", "e a2 d3 c4", "e a2 d3 d4", "e a2 d3 e4",
            "e a2 e3 a4", "e a2 e3 b4", "e a2 e3 c4", "e a2 e3 d4", "e a2 e3 e4",
            "e b2 a3 a4", "e b2 a3 b4", "e b2 a3 c4", "e b2 a3 d4", "e b2 a3 e4",
            "e b2 b3 a4", "e b2 b3 b4", "e b2 b3 c4", "e b2 b3 d4", "e b2 b3 e4",
            "e b2 c3 a4", "e b2 c3 b4", "e b2 c3 c4", "e b2 c3 d4", "e b2 c3 e4",
            "e b2 d3 a4", "e b2 d3 b4", "e b2 d3 c4", "e b2 d3 d4", "e b2 d3 e4",
            "e b2 e3 a4", "e b2 e3 b4", "e b2 e3 c4", "e b2 e3 d4", "e b2 e3 e4",
            "e c2 a3 a4", "e c2 a3 b4", "e c2 a3 c4", "e c2 a3 d4", "e c2 a3 e4",
            "e c2 b3 a4", "e c2 b3 b4", "e c2 b3 c4", "e c2 b3 d4", "e c2 b3 e4",
            "e c2 c3 a4", "e c2 c3 b4", "e c2 c3 c4", "e c2 c3 d4", "e c2 c3 e4",
            "e c2 d3 a4", "e c2 d3 b4", "e c2 d3 c4", "e c2 d3 d4", "e c2 d3 e4",
            "e c2 e3 a4", "e c2 e3 b4", "e c2 e3 c4", "e c2 e3 d4", "e c2 e3 e4",
            "e d2 a3 a4", "e d2 a3 b4", "e d2 a3 c4", "e d2 a3 d4", "e d2 a3 e4",
            "e d2 b3 a4", "e d2 b3 b4", "e d2 b3 c4", "e d2 b3 d4", "e d2 b3 e4",
            "e d2 c3 a4", "e d2 c3 b4", "e d2 c3 c4", "e d2 c3 d4", "e d2 c3 e4",
            "e d2 d3 a4", "e d2 d3 b4", "e d2 d3 c4", "e d2 d3 d4", "e d2 d3 e4",
            "e d2 e3 a4", "e d2 e3 b4", "e d2 e3 c4", "e d2 e3 d4", "e d2 e3 e4",
            "e e2 a3 a4", "e e2 a3 b4", "e e2 a3 c4", "e e2 a3 d4", "e e2 a3 e4",
            "e e2 b3 a4", "e e2 b3 b4", "e e2 b3 c4", "e e2 b3 d4", "e e2 b3 e4",
            "e e2 c3 a4", "e e2 c3 b4", "e e2 c3 c4", "e e2 c3 d4", "e e2 c3 e4",
            "e e2 d3 a4", "e e2 d3 b4", "e e2 d3 c4", "e e2 d3 d4", "e e2 d3 e4",
            "e e2 e3 a4", "e e2 e3 b4", "e e2 e3 c4", "e e2 e3 d4", "e e2 e3 e4" };
