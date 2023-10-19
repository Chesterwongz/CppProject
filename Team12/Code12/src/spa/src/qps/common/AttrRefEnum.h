#pragma once

#include <string>

using std::string;

enum class AttrRefEnum {
  PROC_NAME_ENUM,
  STMT_NUM_ENUM,
  VALUE_ENUM,
  VAR_NAME_ENUM,
  DEFAULT,  // for synonyms without attrRef specified
};
