#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "qps/common/Keywords.h"

using std::string, std::vector, std::unordered_map;

class SynonymResUtils {
 public:
  static const inline vector<AttrRef> ALL_ATTR_REF = {
      ATTR_REF_DEFAULT,  ATTR_REF_PROC_NAME, ATTR_REF_STMT_NUMBER,
      ATTR_REF_VAR_NAME, ATTR_REF_VALUE,
  };

  static const inline string EMPTY_STRING = "";
  static const inline string DELIMITER = "|";

  static string buildKey(unordered_map<AttrRef, string> attributeMap);
};
