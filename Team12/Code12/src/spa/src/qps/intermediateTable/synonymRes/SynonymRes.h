#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "qps/common/AttrRef.h"

using std::string, std::unordered_map, std::unique_ptr;

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
  explicit SynonymRes(string  defaultSynonymValue);
  string toString();
  string getAttribute(AttrRef attrRef);
  // deep clone for polymorphic objects
  [[nodiscard]] virtual unique_ptr<SynonymRes> clone() const;
  bool operator==(const SynonymRes& other) const;
  bool operator!=(const SynonymRes& other) const;

  SynonymRes(const SynonymRes& other) {
    defaultSynonymValue = other.defaultSynonymValue;
    attributeMap = other.attributeMap;
  }

  SynonymRes& operator=(SynonymRes&& other) noexcept = default;
};
