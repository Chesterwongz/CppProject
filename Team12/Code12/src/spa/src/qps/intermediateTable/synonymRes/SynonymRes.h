#pragma once

#include <string>
#include <unordered_map>
#include "qps/common/AttrRef.h"

using std::string, std::unordered_map;

class SynonymRes {
 protected:
  /**
   * defaultSynonymValue is the default value to return
   * when a synonym is referenced without any attrRef:
   * - Stmt      -> Stmt#
   * - Constants -> value
   * - Procedure -> procName
   * - Variable  -> varName
   */
  string defaultSynonymValue;
  unordered_map<AttrRef, string> attributeMap = {};

 public:
  SynonymRes(const string& defaultSynonymValue);
  string toString();
  string getAttribute(AttrRef attrRef);
  bool operator==(const SynonymRes& other);
};
