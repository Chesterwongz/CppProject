#pragma once

#include "common/StmtTypes.h"

namespace common {
constexpr int FIRST_CHILD = 0;
constexpr int LEFT_CHILD = 0;
constexpr int RIGHT_CHILD = 1;
constexpr int INVALID_STMT_NUM = -1;
constexpr int CFG_END_STMT_NUM = 0;
constexpr int WILDCARD_STMT_NUM = -2;
constexpr const char* WILDCARD_PROC = "#WILCARD_PROC#";
constexpr const char* WILDCARD_VAR = "#WILCARD_VAR#";
}  // namespace common
