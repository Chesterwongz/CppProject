#pragma once

#include <string>

using std::string;

enum AttrRef {
  PROC_NAME_ENUM,
  STMT_NUM_ENUM,
  VALUE_ENUM,
  VAR_NAME_ENUM,
  DEFAULT, // for synonyms with attrRef specified
};

inline const string PROC_NAME_ATTR = "procName";
inline const string STMT_NUM_ATTR = "stmt#";
inline const string VALUE_ATTR = "value";
inline const string VAR_NAME_ATTR = "varName";
